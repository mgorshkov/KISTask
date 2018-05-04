#include "stdafx.h"

int main()
{
	ThreadedProducer<Producer> producer;
	ThreadedConsumer<Consumer> consumer;
	Stopper stopper;
	producer.Start();
	consumer.Start();

	std::this_thread::sleep_for(std::chrono::seconds(30));
	
	stopper.Stop();
    return 0;
}

