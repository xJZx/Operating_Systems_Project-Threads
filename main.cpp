#include "Taxi.hpp"
#include "Client.hpp"
#include "Dispatch.hpp"
#include <chrono>
#include <windows.h>
#include <mutex> 
using namespace std;

int main(){

	mutex* mtx = new mutex();

	Dispatch dispatch = Dispatch();
	dispatch.start();

	int taxiID = 0;
	int clientID = 0;

	while (true) {
		if (GetKeyState('T') & 0x8000) {
			Taxi* taxi = new Taxi(taxiID);
			dispatch.addTaxi(taxi);
			cout << "Taxi with id: " << taxiID << " added!" << endl;
			taxiID++;
		}
		if (GetKeyState('C') & 0x8000) {
			Client* client = new Client(clientID);
			client->start();
			dispatch.addClient(client);
			clientID++;
		}
		if (GetKeyState('Q') & 0x8000) {
			mtx->lock();

			vector<Taxi*> taxis = dispatch.getTaxis();
			vector<Client*> clients = dispatch.getClients();

			for(int i = 0; i < taxis.size(); i++){
				taxis[i]->stop();
			}

			for (int i = 0; i < clients.size(); i++) {
				clients[i]->stop();
			}

			dispatch.stop();

			mtx->unlock();

			cout << "The programme has stopped!" << endl;

			break;
		}

		if (GetKeyState('A') & 0x8000) { // jak achtung...
			mtx->lock();

			cout << "Nadchodzi mg³a..." << endl;

			this_thread::sleep_for(chrono::milliseconds(200));

			vector<Taxi*> taxis = dispatch.getTaxis();

			bool clientsDelivered = false;

			while (!clientsDelivered) {
				for (int i = 0; i < taxis.size(); i++) {
					if (taxis[i]->checkAvailability() == true) {
						break;
					}
					if(i == (taxis.size() - 1)) {
						clientsDelivered = true;
					}
				}
			}

			while(true){
				// a mg³a siê unosi...
				if (GetKeyState('A') & 0x8000) {
					break;
				}
			}

			cout << "Koniec mg³y... ale czy aby na pewno...?" << endl;

			mtx->unlock();
		}


		this_thread::sleep_for(chrono::milliseconds(200));
	}

	// this_thread::sleep_for(chrono::seconds(30));
	// client1->stop();
	// taxi1->stop();


	return 0;
}