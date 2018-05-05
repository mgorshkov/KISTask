#pragma once

#include <Windows.h>

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

	void Wait();

private:
	HANDLE mEvent;
};
