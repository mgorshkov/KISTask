#include "stdafx.h"
#include <iostream>

int main()
{
	IStopperPtr stopper = std::make_shared<Stopper>();
	ThreadedProducer<Producer> producer("producer", stopper);
	ThreadedConsumer<Consumer> consumer("consumer", stopper);

	producer.Start();
	consumer.Start();

	std::cout << "Waiting for 30 seconds..." << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(30));
	
	stopper->Stop();
    return 0;
}

