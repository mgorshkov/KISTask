#pragma once

class Consumer : public IConsumer
{
public:
	Consumer(IStopperPtr aStopper);

	void Consume(TaskPtr&& aTask) override;

private:
	IStopperPtr mStopper;
};

