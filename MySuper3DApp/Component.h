#pragma once

#include "includes.h"

class Component
{
public:
	virtual ~Component() {}
	virtual void Initialize() = 0;
	virtual void Update() = 0;
};