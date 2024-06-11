#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <mutex> 
#include "Taxi.hpp"
#include "Client.hpp"
using namespace std;

class Dispatch {
private:
	// arrays of pointers storing all pointers to taxis and clients
	vector<Taxi*> taxis;
	vector<Client*> clients;

	bool isRunning;

	thread dispatchThread;
	mutex mtx;
    condition_variable cvFog;

	bool isFog;

public:
	Dispatch();
	void start();
	void stop();

	void controlLoop();

	void sendTaxiToClient(Taxi*);

	void addTaxi(Taxi*);
	void addClient(Client*);
	void setIsFog();

	vector<Taxi*> getTaxis() {
		return taxis;
	}

	vector<Client*> getClients() {
		return clients;
	}

};