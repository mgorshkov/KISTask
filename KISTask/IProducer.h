#pragma once

#include "Task.h"

class IProducer
{
public:
	virtual ~IProducer() = default;
	virtual TaskPtr Produce() const = 0;
};

