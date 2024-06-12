#include "Taxi.hpp"
#include "Client.hpp"
#include "Dispatch.hpp"
#include "UserInterface.h"
#include <chrono>
#include <windows.h>
#include <mutex>
using namespace std;

int main(){

	mutex* mtx = new mutex();

	Dispatch* dispatch = new Dispatch();
	dispatch->start();

	int taxiID = 0;
	int clientID = 0;

	UserInterface* userInterface = new UserInterface(dispatch);
	userInterface->start();

	while (true) {
		if (GetKeyState('T') & 0x8000) {
			Taxi* taxi = new Taxi(taxiID);
			dispatch->addTaxi(taxi);
			taxiID++;
		}
		if (GetKeyState('C') & 0x8000) {
			Client* client = new Client(clientID);
			client->start();
			dispatch->addClient(client);
			clientID++;
		}
		if (GetKeyState('Q') & 0x8000) {
			mtx->lock();

			vector<Taxi*> taxis = dispatch->getTaxis();
			vector<Client*> clients = dispatch->getClients();

			mtx->unlock();

			for (int i = 0; i < clients.size(); i++) {
				clients[i]->stop();
			}

			// dispatch->getClients().clear();

			for(int i = 0; i < taxis.size(); i++){
				taxis[i]->stop();
			}

			// dispatch->getTaxis().clear();

			userInterface->stop();
			dispatch->stop();

			cout << "The programme has stopped!" << endl;

			break;
		}

		if (GetKeyState('A') & 0x8000) { // as attention...
			//inform dispatcher about bad weather
			userInterface->setIsFog();
			dispatch->setIsFog();
			mtx->lock();

			vector<Taxi*> taxis = dispatch->getTaxis();

			bool clientsDelivered = false;

			while (!clientsDelivered) {
				for (int i = 0; i < taxis.size(); i++) {
					if (taxis[i]->checkAvailability() == false) {
						break;
					}
					if(i == (taxis.size() - 1)) {
						clientsDelivered = true;
					}
				}
			}

			while(true){
				// fog is floating...
				if (GetKeyState('A') & 0x8000) {
					break;
				}
			}

			mtx->unlock();
			// inform about good weather
			dispatch->setIsFog();
			userInterface->setIsFog();
		}


		this_thread::sleep_for(chrono::milliseconds(200));
	}

	// this_thread::sleep_for(chrono::seconds(30));
	// client1->stop();
	// taxi1->stop();


	return 0;
}