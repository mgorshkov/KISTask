#pragma once

#include "defines.h"

class IConsumer
{
public:
	virtual ~IConsumer() = default;
	virtual void Consume(const Task& aTask) = 0;
};
