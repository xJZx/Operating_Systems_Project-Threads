#include "Dispatch.hpp"

Dispatch::Dispatch() {
	isRunning = false;
	isFog = false;
}

void Dispatch::start() {
	if (!isRunning) {
		isRunning = true;
		dispatchThread = std::thread(&Dispatch::controlLoop, this);
	}
}

void Dispatch::stop() {
	if (isRunning) {
		{
			isRunning = false;
		}

		// unblocks the conditional variable in control loop
		cvFog.notify_all();

		dispatchThread.join();

		// just cleaning...
		std::lock_guard<std::mutex> lock(mtx);

		clients.clear();

		taxis.clear();
	}
}

void Dispatch::controlLoop() {
	while (isRunning) {
		std::unique_lock<std::mutex> lock(mtx);

		// conditional variable
		cvFog.wait(lock, [this] { return !isFog || !isRunning; });

		if (!isRunning) break;

		for (Taxi* taxi : taxis) {
			if (taxi->checkAvailability() && !clients.empty()) {
				sendTaxiToClient(taxi);
			}
		}

		lock.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void Dispatch::sendTaxiToClient(Taxi* taxi) {
	taxi->start();
	taxi->setClientID(clients.front()->getClientID());
	clients.front()->stop();
	// cleaning...
	delete clients.front();
	clients.erase(clients.begin());
	taxi->pickUpClient();
}

void Dispatch::addTaxi(Taxi* taxi) {
	std::lock_guard<std::mutex> lock(mtx);
	taxis.push_back(taxi);
}

void Dispatch::addClient(Client* client) {
	std::lock_guard<std::mutex> lock(mtx);
	clients.push_back(client);
}

void Dispatch::setIsFog() {
	{
		std::lock_guard<std::mutex> lock(mtx);
		isFog = !isFog;
	}
	// unblocks the conditional variable in control loop
	cvFog.notify_all();
}
