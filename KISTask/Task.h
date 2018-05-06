#pragma once

#include "original.h"
#include <queue>
#include <memory>

struct Task
{
	explicit Task(Original::Request* aRequest)
		: mRequest(aRequest)
	{
	}

	~Task()
	{
		Original::DeleteRequest(mRequest);
	}

	Task(const Task&) = delete;
	Task& operator = (const Task&) = delete;

	Task(Task&&) = delete;
	Task& operator = (const Task&&) = delete;

	bool IsValid() const
	{
		return mRequest != nullptr;
	}

	Original::Request* mRequest;
};

using TaskPtr = std::unique_ptr<Task>;
using TaskQueue = std::queue<TaskPtr>;
