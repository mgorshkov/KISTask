#pragma once

class Consumer : public IConsumer
{
public:
	Consumer(IStopperPtr aStopper);

	void Consume(const TaskPtr& aTask) override;

private:
	IStopperPtr mStopper;
};

