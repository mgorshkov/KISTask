#pragma once

#include "Task.h"

class IConsumer
{
public:
	virtual ~IConsumer() = default;
	virtual void Consume(const TaskPtr& aTask) = 0;
};
