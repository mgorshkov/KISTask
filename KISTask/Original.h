#pragma once

#include "IStopper.h"

namespace Original
{
	class Request
	{
	};

	using Stopper = ::IStopperPtr;

	Request* GetRequest(Stopper stopSignal);

	void ProcessRequest(Request* request, Stopper stopSignal);

	void DeleteRequest(Request* request);
}
