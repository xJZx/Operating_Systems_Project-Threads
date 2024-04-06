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
	bool isBusy;

	thread taxiThread;


public:
	Taxi(int taxiID);

	void start();
	void stop();
	void drive();

};
