#pragma once
#include <iostream>
#include <thread>
using namespace std;

class Client {
private:
	int clientID;

	bool isRunning;

	thread clientThread;

public:
	Client();

	void start();
	void stop();
	void findTaxi();
};