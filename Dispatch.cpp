#include "Dispatch.hpp"

Dispatch::Dispatch(){
	isRunning = false;
	mtx = new mutex();
}

void Dispatch::start(){
	if (!isRunning) {
		isRunning = true;
		dispatchThread = thread(&Dispatch::controlLoop, this);
	}
}

void Dispatch::stop(){
	if (isRunning) {
		isRunning = false;
		dispatchThread.join();
	}
}

void Dispatch::controlLoop(){
	//cout << this_thread::get_id << endl;
	while (isRunning) {
		mtx->lock();
		if(taxis.size() != 0) {
			for (Taxi* taxi : taxis) {
				if (taxi->checkAvailability()) {
					if (clients.size() > 0) {
						sendTaxiToClient(taxi);
					}
				}
			}
		}
		mtx->unlock();
		//this_thread::sleep_for(chrono::seconds(1));
	}
}

void Dispatch::sendTaxiToClient(Taxi* taxi){
	//mtx->lock();

	taxi->start();
	cout << "Client " << clients.front()->getClientID() << " has been collected by taxi ID: " << taxi->getTaxiID() << "." << endl;
	clients.front()->stop();
	clients.erase(clients.begin());
	taxi->pickUpClient();

	//mtx->unlock();
}

void Dispatch::addTaxi(Taxi* taxi){
	mtx->lock();

	taxis.push_back(taxi);

	mtx->unlock();
}

void Dispatch::addClient(Client* client){
	mtx->lock();

	clients.push_back(client);

	mtx->unlock();
}