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
			TaskPtr task = dependentProducer.Produce();
			if (task == nullptr)
				break; // stop has been detected inside producer
			{
				UniqueLock<Mutex> lk(mSynchronizer.mQueueMutex);
				mSynchronizer.mQueue.emplace(std::move(task));
			}
			mSynchronizer.mCondition.NotifyAll();
		}
	}
};

