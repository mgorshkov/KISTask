#pragma once

#include <Windows.h>

#include "istopper.h"

class Stopper : public IStopper
{
public:
	void Stop() override;

	bool IsStopped() const override;

private:
	volatile LONG mDone{0};
};

