#pragma once

#include "UniqueLock.h"
#include "Mutex.h"

template <typename DependentConsumer>
class ThreadedConsumer : public ThreadedActor
{
public:
	template <typename... Args>
	ThreadedConsumer(Args&&... args)
		: ThreadedActor(std::forward<Args>(args)...)
	{
	}

protected:
	void Run() override
	{
		DependentConsumer dependentConsumer(mSynchronizer.mStopper);
		while (!mSynchronizer.mStopper->IsStopped())
		{
			mSynchronizer.mCondition.Wait();
			ProcessQueue(dependentConsumer);
		}
	}

	void ProcessQueue(IConsumer& aDependentConsumer)
	{
		TaskQueue queue;
		{
			UniqueLock<Mutex> lk(mSynchronizer.mQueueMutex);
			std::swap(mSynchronizer.mQueue, queue);
		}
		while (!queue.empty())
		{
			auto task = queue.front();
			queue.pop();
			aDependentConsumer.Consume(task);
		}
	}
};

