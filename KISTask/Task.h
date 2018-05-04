#pragma once

#include "original.h"
#include <queue>
#include <memory>

struct Task
{
	Task(Original::Request* aRequest)
		: mRequest(aRequest)
	{
	}

	~Task()
	{
		Original::DeleteRequest(mRequest);
	}

	Original::Request* mRequest;
};

using TaskPtr = std::unique_ptr<Task>;
using TaskQueue = std::queue<TaskPtr>;

