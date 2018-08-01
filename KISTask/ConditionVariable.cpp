#include "stdafx.h"

ConditionVariable::ConditionVariable()
{
	mEvents[ModeSignal] = CreateEvent(NULL, FALSE, FALSE, NULL);
	mEvents[ModeBroadcast] = CreateEvent(NULL, TRUE, FALSE, NULL);
}

ConditionVariable::~ConditionVariable()
{
	CloseHandle(mEvents[ModeSignal]);
	CloseHandle(mEvents[ModeBroadcast]);
}

void ConditionVariable::Signal()
{
	mWaitersCountMutex.Lock();
	int haveWaiters = mWaitersCount > 0;
	mWaitersCountMutex.Unlock();

	if (haveWaiters)
		ApiWrapper(SetEvent(mEvents[ModeBroadcast]));
}

void ConditionVariable::Broadcast()
{
	mWaitersCountMutex.Lock();
	int haveWaiters = mWaitersCount > 0;
	mWaitersCountMutex.Unlock();

	if (haveWaiters)
		ApiWrapper(SetEvent(mEvents[ModeBroadcast]));
}

void ConditionVariable::Wait(Mutex& aExternalMutex)
{
	mWaitersCountMutex.Lock();
	mWaitersCount++;
	mWaitersCountMutex.Unlock();

	aExternalMutex.Unlock();
	int result = WaitForMultipleObjects(2, mEvents, FALSE, INFINITE);
	mWaitersCountMutex.Lock();

	mWaitersCount--;
	int lastWaiter =
		result == WAIT_OBJECT_0 + ModeBroadcast
		&& mWaitersCount == 0;
	mWaitersCountMutex.Unlock();

	if (lastWaiter)
		ResetEvent(mEvents[ModeBroadcast]);

	aExternalMutex.Lock();
}
