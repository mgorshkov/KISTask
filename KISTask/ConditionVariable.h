#pragma once

class ConditionVariable
{
public:
	ConditionVariable();
	~ConditionVariable();

	ConditionVariable(const ConditionVariable&) = delete;
	ConditionVariable& operator = (const ConditionVariable&) = delete;

	ConditionVariable(ConditionVariable&&) = delete;
	ConditionVariable& operator = (const ConditionVariable&&) = delete;

	void NotifyAll();

	bool wait(UniqueLock<Mutex>& aLock);

private:
	HANDLE mEvent;
};
