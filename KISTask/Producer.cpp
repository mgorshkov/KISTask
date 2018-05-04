#include "stdafx.h"

Producer::Producer(IStopperPtr aStopper)
	: mStopper(aStopper)
{
}

TaskPtr Producer::Produce() const
{
	auto request = Original::GetRequest(mStopper);
	return request ? std::make_shared<Task>(request) : nullptr;
}

