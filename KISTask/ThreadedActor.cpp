#include "stdafx.h"

#include <iostream>
#include <sstream>
#include "ThreadedActor.h"

ThreadedActor::ThreadedActor(Synchronizer& aSynchronizer, const std::string& aThreadPrefix, int aThreadCount)
	: mSynchronizer(aSynchronizer)
	, mThreadPrefix(aThreadPrefix)
	, mThreadCount(aThreadCount)
	, mIsStarted(false)
{
}

ThreadedActor::~ThreadedActor()
{
	if (mIsStarted)
		std::cerr << "~ThreadedActor on running threads" << std::endl;
}

void ThreadedActor::Start()
{
	for (int i = 0; i < mThreadCount; ++i)
	{
		std::stringstream name;
		name << mThreadPrefix << i;
		mThreads.emplace_back(std::thread(ThreadProc, this, name.str()));
	}
	mIsStarted = true;
}

void ThreadedActor::Stop()
{
	if (!mIsStarted)
		return;
	mSynchronizer.mStopper->Stop();
	mSynchronizer.mCondition.NotifyAll();
	for (auto& thread : mThreads)
		if (thread.joinable())
			thread.join();
	mIsStarted = false;
}

void ThreadedActor::ThreadProc(ThreadedActor* aThis, const std::string& aThreadPrefix)
{
	try
	{
		std::cout << "Thread " << aThreadPrefix << " started." << std::endl;
		aThis->Run();
		std::cout << "Thread " << aThreadPrefix << " stopped." << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Thread " << aThreadPrefix << " failed." << std::endl;
		std::cerr << e.what() << std::endl;
	}
}

