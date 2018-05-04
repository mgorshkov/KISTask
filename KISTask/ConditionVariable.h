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

	bool Wait();

private:
	HANDLE mEvent;
};
