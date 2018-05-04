#pragma once

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
		DependentConsumer dependentConsumer(mStopper);
		while (!mStopper->IsStopped())
		{
			UniqueLock<Mutex> lk(mQueueMutex);
			while (mQueue.empty() && !mStopper->IsStopped())
				mCondition.Wait();
			ProcessQueue(lk, dependentConsumer);
		}
		{
			UniqueLock<Mutex> lk(mQueueMutex);
			ClearQueue(lk, dependentConsumer);
		}
	}

	void ProcessQueue(UniqueLock<Mutex>& lk, IConsumer& aDependentConsumer)
	{
		std::queue<Task> queue;
		std::swap(mQueue, queue);
		lk.Unlock();
		while (!queue.empty())
		{
			const auto& task = queue.front();
			queue.pop();
			aDependentConsumer.Consume(task);
		}
	}

	void ClearQueue(UniqueLock<Mutex>& lk, IConsumer& aDependentConsumer)
	{
		std::queue<Task> queue;
		std::swap(mQueue, queue);
		lk.Unlock();
		while (!queue.empty())
		{
			const auto& task = queue.front();
			queue.pop();
			aDependentConsumer.Clear(task);
		}
	}
};

