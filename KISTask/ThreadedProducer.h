#pragma once

template <typename DependentProducer>
class ThreadedProducer : public ThreadedActor
{
public:
	template <typename... Args>
	ThreadedProducer(Args&&... args)
		: ThreadedActor(std::forward<Args>(args)...)
	{
	}
	
protected:
	void Run() override
	{
		DependentProducer dependentProducer(mSynchronizer.mStopper);
		while (!mSynchronizer.mStopper->IsStopped())
		{
			auto task = dependentProducer.Produce();
			{
				UniqueLock<Mutex> lk(mSynchronizer.mQueueMutex);
				mSynchronizer.mQueue.push(task);
			}
			mSynchronizer.mCondition.NotifyAll();
		}
	}
};

