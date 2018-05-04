#pragma once

class Producer : public IProducer
{
public:
	Producer(IStopperPtr aStopper);

	TaskPtr Produce() const override;

private:
	IStopperPtr mStopper;
};

