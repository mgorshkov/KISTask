#pragma once

#include "Synchronizer.h"

#include <string>
#include <thread>

class ThreadedActor
{
public:
	ThreadedActor(Synchronizer& aSynchronizer, const std::string& aThreadPrefix, int aThreadCount = 2);

	virtual ~ThreadedActor();

	void Start();
	void Stop();

protected:
	virtual void Run() = 0;

	Synchronizer& mSynchronizer;

private:
	static void ThreadProc(ThreadedActor* aThis, const std::string& aThreadPrefix);

	std::string mThreadPrefix;
	int mThreadCount;
	bool mIsStarted;

	std::vector<std::thread> mThreads;
};

