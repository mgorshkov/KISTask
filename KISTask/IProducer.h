#pragma once

#include "defines.h"

class IProducer
{
public:
	virtual ~IProducer() = default;
	virtual Task Produce() const = 0;
};

