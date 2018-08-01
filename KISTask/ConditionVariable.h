#pragma once

#include <Windows.h>
#include "Mutex.h"

class ConditionVariable
{
public:
	ConditionVariable();
	~ConditionVariable();

	ConditionVariable(const ConditionVariable&) = delete;
	ConditionVariable& operator = (const ConditionVariable&) = delete;

	ConditionVariable(ConditionVariable&&) = delete;
	ConditionVariable& operator = (const ConditionVariable&&) = delete;

	void Signal();

	void Broadcast();

	void Wait(Mutex& aExternalMutex);

private:
	enum
	{
		ModeSignal,
		ModeBroadcast,
		NumEvents
	};
	HANDLE mEvents[NumEvents];

	unsigned int mWaitersCount{0};
	Mutex mWaitersCountMutex;
};
