#include "Taxi.hpp"
#include "Client.hpp"
#include "Dispatch.hpp"
#include <chrono>

int main(){

	Dispatch dispatch = Dispatch();
	dispatch.start();

	for (int i = 0; i < 1; i++) {
		Taxi* taxi = new Taxi(i);
		dispatch.addTaxi(taxi);
	}

	for (int i = 0; i < 3; i++) {
		Client* client = new Client(i);
		client->start();
		dispatch.addClient(client);
	}	
		
	this_thread::sleep_for(chrono::seconds(30));
	dispatch.stop();
	//client1->stop();
	//taxi1->stop();


	return 0;
}