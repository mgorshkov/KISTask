#pragma once

#include "Task.h"
#include "IStopper.h"
#include "ConditionVariable.h"
#include "Mutex.h"

struct Synchronizer
{
public:
	explicit Synchronizer(IStopperPtr aStopper);

	void EnqueueTask(TaskPtr&& aTask);
	TaskPtr GetQueueElement();

	void Wait(Mutex& aMutex);

	void Stop();

	bool IsStopped() const;

	TaskQueue mQueue;
	ConditionVariable mCondition;
	Mutex mQueueMutex;
	std::shared_ptr<IStopper> mStopper;
};
