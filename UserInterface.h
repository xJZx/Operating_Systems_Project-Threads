#pragma once
#include <vector>
#include "Taxi.hpp"
#include "Client.hpp"
#include "Dispatch.hpp"
#include <windows.h>
#include <thread>
#include <iostream>
#include "Dispatch.hpp"
using namespace std;

class UserInterface {
private:
	thread uiThread;
	bool isRunning;
	bool isFog;
	void print();
	Dispatch* dispatch;
	mutex* mtx;

public:
	UserInterface(Dispatch*);
	void start();
	void stop();
	void setIsFog();
};