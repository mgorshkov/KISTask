#pragma once

class Producer : public IProducer
{
public:
	Producer(IStopperPtr aStopper);

	Task Produce() const override;

private:
	IStopperPtr mStopper;
};

