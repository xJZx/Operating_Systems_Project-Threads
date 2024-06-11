#pragma once
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;


class Taxi {
private:
	int taxiID;
	// variable: is thread running
	bool isRunning;

	//variable: is taxi free
	bool isAvailable;
	int clientID;

	thread taxiThread;


public:
	Taxi(int taxiID);

	void start();
	void stop();
	void drive();
	bool checkAvailability();
	void setIsBusy();
	void pickUpClient();
	int getTaxiID();
	void setClientID(int clientID);
	int getClientID();

};
