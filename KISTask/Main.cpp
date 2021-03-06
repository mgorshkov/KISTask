#include "stdafx.h"
#include <iostream>

int main()
{
	try
	{
		IStopperPtr stopper = std::make_shared<Stopper>();
		Synchronizer synchronizer(stopper);
		ThreadedProducer<Producer> producer(synchronizer, "producer");
		ThreadedConsumer<Consumer> consumer(synchronizer, "consumer");

		producer.Start();
		consumer.Start();

		std::cout << "Waiting for 30 seconds..." << std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(30));

		synchronizer.Stop();

		producer.Join();
		consumer.Join();
	}
	catch (const std::exception& e)
	{
		std::cout << "Main thread failed." << std::endl;
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

