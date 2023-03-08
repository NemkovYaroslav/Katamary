#include "RenderComponent.h"
#include "Game.h"
#include "DisplayWin32.h"
#include "Camera.h"
#include "RenderSystem.h"
#define _USE_MATH_DEFINES
#include <math.h>

RenderComponent::RenderComponent(std::string shaderFileName, D3D_PRIMITIVE_TOPOLOGY topology) : Component()
{
	this->shaderFileName = shaderFileName;
	this->topology = topology;
}

RenderComponent::~RenderComponent()
{
	Game::GetInstance()->GetRenderSystem()->RemoveRenderComponent(this);
}

void RenderComponent::Initialize()
{
	Game::GetInstance()->GetRenderSystem()->renderComponents.push_back(this);
	std::wstring fileName(shaderFileName.begin(), shaderFileName.end());
	ID3DBlob* errorCode = nullptr;

	Microsoft::WRL::ComPtr<ID3DBlob> vertexShaderByteCode;
	auto res = D3DCompileFromFile(
		fileName.c_str(),
		nullptr /*macros*/,
		nullptr /*include*/,
		"VSMain",
		"vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		vertexShaderByteCode.GetAddressOf(),
		&errorCode
	);
	if (FAILED(res))
	{
		// If the shader failed to compile it should have written something to the error message.
		if (errorCode)
		{
			const char* compileErrors = (char*)(errorCode->GetBufferPointer());
			std::cout << compileErrors << std::endl;
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			std::cout << "Missing Shader File: " << shaderFileName << std::endl;
		}
		return;
	}
	Game::GetInstance()->GetRenderSystem()->device->CreateVertexShader(
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		nullptr, vertexShader.GetAddressOf()
	);

	Microsoft::WRL::ComPtr<ID3DBlob> pixelShaderByteCode;
	res = D3DCompileFromFile(
		fileName.c_str(),
		nullptr /*macros*/,
		nullptr /*include*/,
		"PSMain",
		"ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		pixelShaderByteCode.GetAddressOf(),
		&errorCode
	);
	Game::GetInstance()->GetRenderSystem()->device->CreatePixelShader(
		pixelShaderByteCode->GetBufferPointer(),
		pixelShaderByteCode->GetBufferSize(),
		nullptr, pixelShader.GetAddressOf()
	);

	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0},
		D3D11_INPUT_ELEMENT_DESC {
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0}
	};

	Game::GetInstance()->GetRenderSystem()->device->CreateInputLayout(
		inputElements,
		2,
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		inputLayout.GetAddressOf()
	);

	D3D11_BUFFER_DESC vertexBufDesc = {};
	vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufDesc.CPUAccessFlags = 0;
	vertexBufDesc.MiscFlags = 0;
	vertexBufDesc.StructureByteStride = 0;
	vertexBufDesc.ByteWidth = sizeof(DirectX::XMFLOAT4) * std::size(points);

	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = points.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	Game::GetInstance()->GetRenderSystem()->device->CreateBuffer(&vertexBufDesc, &vertexData, vertexBuffer.GetAddressOf());

	D3D11_BUFFER_DESC indexBufDesc = {};
	indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufDesc.CPUAccessFlags = 0;
	indexBufDesc.MiscFlags = 0;
	indexBufDesc.StructureByteStride = 0;
	indexBufDesc.ByteWidth = sizeof(int) * std::size(indices);

	D3D11_SUBRESOURCE_DATA indexData = {};
	indexData.pSysMem = indices.data();
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	Game::GetInstance()->GetRenderSystem()->device->CreateBuffer(&indexBufDesc, &indexData, indexBuffer.GetAddressOf());

	D3D11_BUFFER_DESC constBufDesc = {};
	constBufDesc.Usage = D3D11_USAGE_DEFAULT;
	constBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constBufDesc.CPUAccessFlags = 0;
	constBufDesc.MiscFlags = 0;
	constBufDesc.StructureByteStride = 0;
	constBufDesc.ByteWidth = sizeof(DirectX::XMMATRIX);
	Game::GetInstance()->GetRenderSystem()->device->CreateBuffer(&constBufDesc, nullptr, constBuffer.GetAddressOf());

	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.FillMode = D3D11_FILL_SOLID;
	Game::GetInstance()->GetRenderSystem()->device->CreateRasterizerState(&rastDesc, rastState.GetAddressOf());
}

void RenderComponent::Update()
{
	DirectX::XMMATRIX worldViewProjectionMatrix = Game::GetInstance()->GetCamera()->GetWorldViewProjectionMatrix(World);
	DirectX::XMMATRIX ScaledMatrix = DirectX::XMMatrixScaling(
		static_cast<float>(Game::GetInstance()->GetDisplay()->GetClientHeight())
		/ 
		static_cast<float>(Game::GetInstance()->GetDisplay()->GetClientWidth()),
		1.0f,
		1.0f\
	);
	DirectX::XMMATRIX Transform = DirectX::XMMatrixTranspose(DirectX::XMMatrixMultiply(ScaledMatrix, worldViewProjectionMatrix));
	Game::GetInstance()->GetRenderSystem()->context->UpdateSubresource(constBuffer.Get(), 0, nullptr, &Transform, 0, 0);
}

void RenderComponent::Draw()
{
	Game::GetInstance()->GetRenderSystem()->context->RSSetState(rastState.Get());
	Game::GetInstance()->GetRenderSystem()->context->IASetInputLayout(inputLayout.Get());
	Game::GetInstance()->GetRenderSystem()->context->IASetPrimitiveTopology(topology);
	Game::GetInstance()->GetRenderSystem()->context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	UINT strides[] = { 32 };
	UINT offsets[] = { 0 };
	Game::GetInstance()->GetRenderSystem()->context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), strides, offsets);
	Game::GetInstance()->GetRenderSystem()->context->VSSetShader(vertexShader.Get(), nullptr, 0);
	Game::GetInstance()->GetRenderSystem()->context->VSSetConstantBuffers(0, 1, constBuffer.GetAddressOf());
	Game::GetInstance()->GetRenderSystem()->context->PSSetShader(pixelShader.Get(), nullptr, 0);
	Game::GetInstance()->GetRenderSystem()->context->DrawIndexed(indices.size(), 0, 0);
}

void RenderComponent::AddCube(float radius)
{
	points = {
		Vector4(-radius,   radius, -radius, 1.0f),  Vector4(0.1f, 0.9f, 0.7f, 1.0f),
		Vector4(radius,   radius, -radius, 1.0f),  Vector4(0.2f, 1.0f, 0.8f, 1.0f),
		Vector4(radius,   radius,   radius, 1.0f),  Vector4(0.3f, 0.1f, 0.9f, 1.0f),
		Vector4(-radius,   radius,   radius, 1.0f),  Vector4(0.4f, 0.2f, 1.0f, 1.0f),
		Vector4(-radius, -radius, -radius, 1.0f),  Vector4(0.5f, 0.3f, 0.1f, 1.0f),
		Vector4(radius, -radius, -radius, 1.0f),  Vector4(0.6f, 0.4f, 0.2f, 1.0f),
		Vector4(radius, -radius,   radius, 1.0f),  Vector4(0.7f, 0.5f, 0.3f, 1.0f),
		Vector4(-radius, -radius,   radius, 1.0f),  Vector4(0.8f, 0.6f, 0.4f, 1.0f)

	};
	indices = {
		3,1,0,
		2,1,3,

		0,5,4,
		1,5,0,

		3,4,7,
		0,4,3,

		1,6,5,
		2,6,1,

		2,7,6,
		3,7,2,

		6,4,5,
		7,4,6
	};

}
void RenderComponent::AddSphere(float radius, int sliceCount, int stackCount, DirectX::XMFLOAT4 color)
{
	int g = 0;
	points.push_back(DirectX::XMFLOAT4(0, radius, 0, 1));
	points.push_back(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	auto phiStep = M_PI / stackCount;
	auto thetaStep = 2.0f * M_PI / sliceCount;
	DirectX::XMFLOAT4 colorBase[] = { { 1.0f, 0.3f, 0.3f, 1.0f }, { 0.5f, 1.0f, 0.5f, 1.0f }, { 0.7f, 0.7f, 1.0f, 1.0f }, { 0.9f, 0.9f, 0.9f, 1.0f } };
	for (int i = 1; i <= stackCount - 1; i++)
	{
		auto phi = i * phiStep;
		for (int j = 0; j <= sliceCount; j++)
		{
			if (((j / 20 == g)) && (g < 4))
			{
				color = colorBase[g++];
			}
			auto theta = j * thetaStep;
			points.push_back(
				DirectX::XMFLOAT4(
					radius * sin(phi) * cos(theta),
					radius * cos(phi),
					radius * sin(phi) * sin(theta),
					1.0f)
			);
			points.push_back(color);
		}
		g = 0;
	}
	points.push_back(DirectX::XMFLOAT4(0, -radius, 0, 1));
	points.push_back(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	for (int i = 1; i <= sliceCount; i++)
	{
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i);
	}
	auto baseIndex = 1;
	auto ringVertexCount = sliceCount + 1;
	for (int i = 0; i < stackCount - 2; i++)
	{
		for (int j = 0; j < sliceCount; j++)
		{
			indices.push_back(baseIndex + i * ringVertexCount + j);
			indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
		}
	}

	auto southPoleIndex = indices.size() - 1;
	baseIndex = southPoleIndex - ringVertexCount;
	for (int i = 0; i < sliceCount; i++)
	{
		indices.push_back(southPoleIndex);
		indices.push_back(baseIndex + i);
		indices.push_back(baseIndex + i + 1);
	}

}
void RenderComponent::AddGrid(int gridSize, float cellSize, Color color)
{

	int firstPointIndex = points.size() / 2;
	int nPoints = gridSize * 2 + 1;
	float offset = -(nPoints / 2) * cellSize;
	for (int i = 0; i < nPoints; i++)
	{
		for (int j = 0; j < nPoints; j++)
		{
			points.push_back(Vector4(cellSize * i + offset, 0, cellSize * j + offset, 1));
			points.push_back(color);

			if (i == nPoints / 2 && j == nPoints / 2)
			{
				continue;
			}
			if (j < nPoints - 1)
			{
				indices.push_back(firstPointIndex + i * nPoints + j);
				indices.push_back(firstPointIndex + i * nPoints + j + 1);
			}
			if (i < nPoints - 1)
			{
				indices.push_back(firstPointIndex + i * nPoints + j);
				indices.push_back(firstPointIndex + i * nPoints + j + nPoints);
			}
		}
	}
	// COORDINATE AXIS
		//AddLine(Vector4(0, 0, 0, 1), Vector4(cellSize, 0, 0, 1), Color(1, 0, 0, 1));
		//AddLine(Vector4(0, 0, 0, 1), Vector4(0, cellSize, 0, 1), Color(0, 1, 0, 1));
		//AddLine(Vector4(0, 0, 0, 1), Vector4(0, 0, cellSize, 1), Color(0, 0, 1, 1));
	// COORDINATE AXIS
}