#include "Dispatch.hpp"

Dispatch::Dispatch(){
	isRunning = false;
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
	while (isRunning) {

		for(Taxi* taxi : taxis){
			if(taxi->checkAvailability()){
				if(clients.size() > 0){
					sendTaxiToClient(taxi);
				}
			}
		}
	}
}

void Dispatch::sendTaxiToClient(Taxi* taxi){
	taxi->start();
	cout << "Client " << clients.front()->getClientID() << " has been collected by taxi ID: " << taxi->getTaxiID() << "." << endl;
	clients.front()->stop();
	clients.erase(clients.begin());
	taxi->pickUpClient();
}

void Dispatch::addTaxi(Taxi* taxi){
	taxis.push_back(taxi);
}

void Dispatch::addClient(Client* client){
	clients.push_back(client);
}