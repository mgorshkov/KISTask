#include "stdafx.h"

Consumer::Consumer(IStopperPtr aStopper)
	: mStopper(aStopper)
{
}

void Consumer::Consume(const Task& aTask)
{
	Original::ProcessRequest(aTask.mRequest, mStopper);
}

