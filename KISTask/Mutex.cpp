#include "stdafx.h"

Mutex::Mutex()
{
	ApiWrapper((mMutex = CreateMutex(NULL, FALSE, NULL)) != NULL);
}

Mutex::~Mutex()
{
	CloseHandle(mMutex);
}

void Mutex::Lock()
{
	ApiWrapper(WAIT_FAILED != WaitForSingleObject(mMutex, INFINITE));
}

void Mutex::Unlock()
{
	ApiWrapper(ReleaseMutex(mMutex));
}
