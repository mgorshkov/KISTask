#pragma once

class Producer : public IProducer
{
public:
	explicit Producer(IStopperPtr aStopper);

	TaskPtr Produce() const override;

private:
	IStopperPtr mStopper;
};

