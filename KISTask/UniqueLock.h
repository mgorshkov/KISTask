#pragma once

template <typename M>
class UniqueLock
{
public:
	explicit UniqueLock(M& aMutex)
		: mMutex(&aMutex)
		, mOwns(false)
	{
		mMutex->Lock();
		mOwns = true;
	}

	~UniqueLock()
	{
		if (mOwns)
			mMutex->Unlock();
	}

	UniqueLock(UniqueLock&& aOther)
		: mMutex(aOther.mMutex)
		, mOwns(aOther.mOwns)
	{
		aOther.mMutex = 0;
		aOther.mOwns = false;
	}

	UniqueLock& operator = (UniqueLock&& aOther)
	{
		if (this != &aOther)
		{
			if (mOwns)
				mMutex->Unlock();
			mMutex = aOther.mMutex;
			mOwns = aOther.mOwns;
			aOther.mMutex = nullptr;
			aOther.mOwns = false;	
		}
		return *this;
	}

	UniqueLock(const UniqueLock&) = delete;
	UniqueLock& operator = (const UniqueLock&) = delete;

private:
	M* mMutex;
	bool mOwns;
};
