#include "Client.hpp"

Client::Client(int clientID){
	this->clientID = clientID;
	isRunning = false;
}

void Client::start(){
	if (!isRunning) {
		isRunning = true;
		clientThread = thread(&Client::findTaxi, this);
	}
}

void Client::stop(){
	if (isRunning) {
		isRunning = false;
		clientThread.join();
	}
}

void Client::findTaxi(){
	while (isRunning) {
		//cout << "Client " << clientID << " is seeking taxi..." << endl;
		this_thread::sleep_for(chrono::seconds(3));
	}
}

int Client::getClientID() {
	return clientID;
}