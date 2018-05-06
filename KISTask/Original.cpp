#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

namespace Original
{
	Request* GetRequest(Stopper stopSignal)
	{
		if (stopSignal->IsStopped())
			return nullptr;
		// payload
		std::vector<int> v(1000);
		std::iota(v.begin(), v.end(), 0);
		for (int i = 0; i < 10000; ++i)
		{
			if (stopSignal->IsStopped())
				return nullptr;
			std::random_shuffle(v.begin(), v.end());
		}
		auto request = new Request{};
		std::cout << "GetRequest: " << request << std::endl;
		return request;
	}

	void ProcessRequest(Request* request, Stopper stopSignal)
	{
		if (stopSignal->IsStopped())
			return;
		// payload
		std::vector<int> v(1000);
		std::iota(v.begin(), v.end(), 0);
		for (int i = 0; i < 10000; ++i)
		{
			if (stopSignal->IsStopped())
				return;
			std::random_shuffle(v.begin(), v.end());
		}
		std::cout << "ProcessRequest: " << request << std::endl;
	}

	void DeleteRequest(Request* request)
	{
		std::cout << "DeleteRequest: " << request << std::endl;
		delete request;
	}
}