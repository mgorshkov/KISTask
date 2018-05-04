#include "stdafx.h"

#include <iostream>
#include <sstream>
#include "ThreadedActor.h"

ThreadedActor::ThreadedActor(const std::string& aThreadPrefix, IStopperPtr aStopper, int aThreadCount)
	: mThreadPrefix(aThreadPrefix)
	, mStopper(aStopper)
	, mThreadCount(aThreadCount)
{
}

ThreadedActor::~ThreadedActor()
{
	Stop();
}

void ThreadedActor::Start()
{
	for (int i = 0; i < mThreadCount; ++i)
	{
		std::stringstream name;
		name << mThreadPrefix << i;
		mThreads.emplace_back(std::thread(ThreadProc, this, name.str()));
	}
}

void ThreadedActor::Stop()
{
	mStopper->Stop();
	mCondition.NotifyAll();
	for (auto& thread : mThreads)
		if (thread.joinable())
			thread.join();
}

void ThreadedActor::ThreadProc(ThreadedActor* aThis, const std::string& aThreadPrefix)
{
	try
	{
		std::cout << "Thread " << aThreadPrefix << " started.";
		aThis->Run();
		std::cout << "Thread " << aThreadPrefix << " stopped.";
	}
	catch (const std::exception &e)
	{
		std::cout << "Thread " << aThreadPrefix << " errored.";
		std::cerr << e.what() << std::endl;
	}
}

