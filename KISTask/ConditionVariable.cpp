#include "stdafx.h"
#include "ApiWrapper.h"
#include "ConditionVariable.h"

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

bool ConditionVariable::Wait()
{
	DWORD res = WaitForSingleObject(mEvent, INFINITE);
	ApiWrapper(res != WAIT_FAILED);
	return WAIT_OBJECT_0 == res;
}
