#pragma once

class Consumer : public IConsumer
{
public:
	Consumer(IStopperPtr aStopper);

	void Consume(const Task& aTask) override;

	void Clear(const Task& aTask) override;

private:
	IStopperPtr mStopper;
};

