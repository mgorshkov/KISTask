#include "stdafx.h"

Mutex::Mutex()
{
	mMutex = CreateMutex(NULL, FALSE, NULL);
}

void Mutex::Lock()
{
	auto result = WaitForSingleObject(mMutex, INFINITE);
}

void Mutex::Unlock()
{
	ReleaseMutex(mMutex);
}

Mutex::~Mutex()
{
	CloseHandle(mMutex);
}