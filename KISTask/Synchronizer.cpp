#include "stdafx.h"

Synchronizer::Synchronizer(IStopperPtr aStopper)
	: mStopper(aStopper)
{
}

void Synchronizer::Stop()
{
	mStopper->Stop();
	mCondition.NotifyAll();
}

