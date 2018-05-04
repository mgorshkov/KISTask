#pragma once

template <typename M>
class UniqueLock
{
public:
	explicit UniqueLock(M& aMutex)
		: mMutex(&aMutex)
	{
		mMutex->Lock();
	}

	~UniqueLock()
	{
		mMutex->Unlock();
	}

	UniqueLock(UniqueLock&& aOther)
		: mMutex(aOther.mMutex)
	{
		aOther.mMutex = 0;
	}

	UniqueLock& operator = (UniqueLock&& aOther)
	{
		if (this != &aOther)
		{
			mMutex->Unlock();
			mMutex = aOther.mMutex;
			aOther.mMutex = nullptr;
		}
		return *this;
	}

	UniqueLock(const UniqueLock&) = delete;
	UniqueLock& operator = (const UniqueLock&) = delete;

	void Unlock()
	{
		mMutex->Unlock();
	}

private:
	M* mMutex;
};
