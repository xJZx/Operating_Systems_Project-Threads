#include "Taxi.hpp"
#include "Client.hpp"
#include "Dispatch.hpp"
#include <chrono>

int main(){

	Taxi taxi1 = Taxi(69);
	taxi1.start();
	this_thread::sleep_for(chrono::seconds(10));
	taxi1.stop();


	return 0;
}