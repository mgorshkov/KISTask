#include "stdafx.h"
#include "ConditionVariable.h"

ConditionVariable::ConditionVariable()
{
	ApiWrapper(mEvent = CreateEvent(NULL, FALSE, FALSE, NULL));

}

ConditionVariable::~ConditionVariable()
{
	CloseHandler(mEvent);
}

void ConditionVariable::NotifyAll()
{
	SetEvent(mEvent);
}

bool ConditionVariable::wait(UniqueLock<Mutex>& aLock)
{
	auto result = WAIT_OBJECT_0 == WaitForSingleObject(mEvent, INFINITE);
	aLock.Unlock();
	return result;
}
