#include "Taxi.hpp"

Taxi::Taxi(int taxiID){
	this->taxiID = taxiID;
	isRunning = false;
	isAvailable = true;
}

void Taxi::start(){
	if (!isRunning) {
		isRunning = true;
		taxiThread = thread(&Taxi::drive, this);
	}
}

void Taxi::stop(){
	if(isRunning){
		isRunning = false;
		taxiThread.join();
	}
}

void Taxi::drive(){
	while (isRunning) {
		cout << "Taxi " << taxiID << " is driving around..." << endl;
		this_thread::sleep_for(chrono::seconds(2));
	}
	cout << "Taxi " << taxiID << " has stopped." << endl;
}

bool Taxi::checkAvailability() {
	return isAvailable;
}

void Taxi::setIsBusy() {
	isAvailable = !isAvailable;
}

void Taxi::pickUpClient() {
	// taxi is busy with a client
	setIsBusy();

	srand(time(NULL));
	// simulates time taxi is driving the client
	int transportTime = 5 + (rand() % 5);
	this_thread::sleep_for(chrono::seconds(transportTime));

	cout << "Client has been dropped off by taxi: " << taxiID << "." << endl;

	// taxi is free
	setIsBusy();
}

int Taxi::getTaxiID() {
	return taxiID;
}