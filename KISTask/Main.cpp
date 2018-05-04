#include "stdafx.h"
#include <iostream>

int main()
{
	IStopperPtr stopper = std::make_shared<Stopper>();
	Synchronizer synchronizer(stopper);
	ThreadedProducer<Producer> producer(synchronizer, "producer");
	ThreadedConsumer<Consumer> consumer(synchronizer, "consumer");

	producer.Start();
	consumer.Start();

	std::cout << "Waiting for 30 seconds..." << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(30));
	
	producer.Stop();
	consumer.Stop();

	return 0;
}

