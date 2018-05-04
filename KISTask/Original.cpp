#include "stdafx.h"

#include <algorithm>
#include <numeric>
#include <vector>

#include "original.h"

namespace Original
{
	Request* GetRequest(Stopper stopSignal)
	{
		if (stopSignal->IsStopped())
			return nullptr;
		// payload
		std::vector<int> v(1000);
		std::iota(v.begin(), v.end(), 0);
		for (int i = 0; i < 1000000; ++i)
		{
			if (stopSignal->IsStopped())
				return nullptr;
			std::random_shuffle(v.begin(), v.end());
		}
		return new Request{};
	}

	void ProcessRequest(Request* request, Stopper stopSignal)
	{
		if (stopSignal->IsStopped())
			return;
		// payload
		std::vector<int> v(1000);
		std::iota(v.begin(), v.end(), 0);
		for (int i = 0; i < 1000000; ++i)
		{
			if (stopSignal->IsStopped())
				return;
			std::random_shuffle(v.begin(), v.end());
		}
	}

	void DeleteRequest(Request* request)
	{
		delete request;
	}
}