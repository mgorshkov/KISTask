#pragma once

#include <Windows.h>

class Mutex
{
public:
	Mutex();
	~Mutex();

	Mutex(const Mutex&) = delete;
	Mutex& operator = (const Mutex&) = delete;

	Mutex(Mutex&&) = delete;
	Mutex& operator = (const Mutex&&) = delete;

	void Lock();
	void Unlock();

private:
	HANDLE mMutex;
};
