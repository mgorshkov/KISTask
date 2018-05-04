#pragma once

#include "Task.h"

class IConsumer
{
public:
	virtual ~IConsumer() = default;
	virtual void Consume(TaskPtr&& aTask) = 0;
};
