#pragma once

template <typename DependentProducer>
class ThreadedProducer : public ThreadedActor
{
public:
	template <typename... Args>
	ThreadedProducer(Args... args)
		: ThreadedActor(std::forward<Args...>(args...))
	{
	}
	
	void Run() override
	{
		DependentProducer dependentProducer(mStopper);
		while (!mStopper->IsStopped())
		{
			auto task = dependentProducer.Produce();
			{
				UniqueLock<Mutex> lk(mQueueMutex);
				mQueue.push(task);
			}
			mCondition.NotifyAll();
		}
	}
};

