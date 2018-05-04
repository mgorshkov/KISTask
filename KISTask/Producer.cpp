#include "stdafx.h"

Producer::Producer(IStopperPtr aStopper)
	: mStopper(aStopper)
{
}

Task Producer::Produce() const
{
	auto request = Original::GetRequest(mStopper);
	return Task{request};
}

