#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include "Taxi.hpp"
#include "Client.hpp"
using namespace std;

class Dispatch {
private:
	// arrays storing all taxis and clients
	vector<Taxi> taxis;
	vector<Client> clients;

	bool isRunning;

	thread dispatchThread;

public:
	Dispatch();
	void start();
	void stop();

	void controlLoop();

	void sendTaxiToClient(Taxi, Client);

};