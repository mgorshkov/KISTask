#pragma once

#include <string>
#include <queue>
#include <thread>

#include "Defines.h"
#include "IStopper.h"
#include "ConditionVariable.h"
#include "Mutex.h"

class ThreadedActor
{
public:
	ThreadedActor(const std::string& aThreadPrefix, IStopperPtr aStopper, int aThreadCount = 2);

	virtual ~ThreadedActor();

	virtual void Run() = 0;

	void Start();

	void Stop();

protected:
	std::queue<Task> mQueue;
	ConditionVariable mCondition;
	Mutex mQueueMutex;
	std::shared_ptr<IStopper> mStopper;

private:
	static void ThreadProc(ThreadedActor* aThis, const std::string& aThreadPrefix);

	std::string mThreadPrefix;
	int mThreadCount;

	std::vector<std::thread> mThreads;
};

