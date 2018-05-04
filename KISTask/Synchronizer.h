#pragma once

#include "Task.h"
#include "IStopper.h"
#include "ConditionVariable.h"
#include "Mutex.h"

struct Synchronizer
{
	Synchronizer(IStopperPtr aStopper);

	TaskQueue mQueue;
	ConditionVariable mCondition;
	Mutex mQueueMutex;
	std::shared_ptr<IStopper> mStopper;
};
