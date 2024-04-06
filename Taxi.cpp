#include "Taxi.hpp"

Taxi::Taxi(int taxiID){
	this->taxiID = taxiID;
	isRunning = false;
	isBusy = false;
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