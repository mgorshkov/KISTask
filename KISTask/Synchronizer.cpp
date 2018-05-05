#include "stdafx.h"

Synchronizer::Synchronizer(IStopperPtr aStopper)
	: mStopper(aStopper)
{
}

void Synchronizer::EnqueueTask(TaskPtr&& aTask)
{
	{
		UniqueLock<Mutex> lk(mQueueMutex);
		mQueue.emplace(std::move(aTask));
	}
	mCondition.NotifyAll();
}

TaskQueue Synchronizer::GetQueue()
{
	TaskQueue queue;
	UniqueLock<Mutex> lk(mQueueMutex);
	std::swap(mQueue, queue);
	return queue;
}

void Synchronizer::Wait()
{
	mCondition.Wait();
}

void Synchronizer::Stop()
{
	mStopper->Stop();
	mCondition.NotifyAll();
}

bool Synchronizer::IsStopped() const
{
	return mStopper->IsStopped();
}
