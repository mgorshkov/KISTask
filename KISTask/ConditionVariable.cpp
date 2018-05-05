#include "stdafx.h"

ConditionVariable::ConditionVariable()
{
	ApiWrapper((mEvent = CreateEvent(NULL, FALSE, FALSE, NULL)) != NULL);
}

ConditionVariable::~ConditionVariable()
{
	CloseHandle(mEvent);
}

void ConditionVariable::NotifyAll()
{
	ApiWrapper(SetEvent(mEvent));
}

void ConditionVariable::Wait()
{
	ApiWrapper(WAIT_FAILED != WaitForSingleObject(mEvent, INFINITE));
}
