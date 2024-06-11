#include "UserInterface.h"

UserInterface::UserInterface(Dispatch* dispatch) {
	isRunning = false;
	isFog = false;
	this->dispatch = dispatch;
	mtx = new mutex();
}

void UserInterface::start() {
	if (!isRunning) {
		isRunning = true;
		uiThread = thread(&UserInterface::print, this);
	}
}

void UserInterface::print() {
	while (isRunning) {
		//print parking
		mtx->lock();
		vector<Taxi*> taxis = dispatch->getTaxis();
		vector<Client*> clients = dispatch->getClients();
		system("CLS");
		for (int i = 0; i < taxis.size(); i++) {
			cout << taxis[i]->getTaxiID();
			if (taxis[i]->getTaxiID() / 10 == 0) {
				cout << "-----|";
			}
			else {
				cout << "----|";
			}
		}
		cout << endl;
		for (int i = 0; i < taxis.size(); i++) {
			cout << "|     |";
		}
		cout << endl;
		for (int i = 0; i < taxis.size(); i++) {
			cout << "|";
			if (taxis[i]->checkAvailability()) {
				cout << "F    |";
			}

			else {
				cout << "B=" << taxis[i]->getClientID();
				if (taxis[i]->getClientID() / 10 == 0) {
					cout << "  |";
				}
				else {
					cout << " |";
				}
			}

		}
		cout << endl;

		for (int i = 0; i < taxis.size(); i++) {
			cout << "|     |";
		}
		cout << endl;
		for (int i = 0; i < taxis.size(); i++) {
			cout << "|-----|";
		}
		cout << endl;

		cout << "List of available clients: ";
		for (int i = 0; i < clients.size(); i++) {
			cout << clients[i]->getClientID() << " ";
		}
		cout << endl;

		cout << "More detailed info:" << endl;
		if (isFog) {
			cout << "Fog..." << endl;
		}
		mtx->unlock();
	}
}

void UserInterface::stop() {
	if (isRunning) {
		isRunning = false;
		uiThread.join();
	}
}

void UserInterface::setIsFog() {
	isFog = !isFog;
}