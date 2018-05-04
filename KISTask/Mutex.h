#pragma once

class Mutex
{
public:
	Mutex();
	void Lock();
	void Unlock();
	~Mutex();

private:
	HANDLE mMutex;
};
