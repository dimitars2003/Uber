#include "ClientConsole.h"
#include <fstream>
#include <iostream>


void ClientConsole::logedInMenu()  {

	std::cout << "Hello " << getClients()[indexCurrentClient].getFirstName()<<".\n";
	int choice = -1;
	while (true) {
		std::cout << "Client Menu\n";
		std::cout << "Current Balance: " << getClients()[indexCurrentClient].getBalance();
		std::cout << "Enter the number of the action you wish to do\n";
		std::cout << "Order - 1\n";
		std::cout << "Check order information - 2\n";
		std::cout << "Cancel order - 3\n";
		std::cout << "Pay order - 4\n";
		std::cout << "Rate order - 5\n";
		std::cout << "Add money to balance - 6\n";
		std::cout << "To log out - 0\n";

		std::cin >> choice;

		if (choice == 0) {
			
			return;
		}

		if (choice == 1) {
			order();
		}	

		if (choice == 2) {
			checkOrder();
		}

		if (choice == 3) {
			cancelOrder();
		}
		
		if (choice == 4) {
			pay();
		}
		
		if (choice == 5) {
			rate();
		}
		
		if (choice == 6) {
			add_money();
		}

	}
}

ClientConsole::ClientConsole() : ConsoleBase() {
	
}

void ClientConsole::login()  {
	
	MyString username;
	MyString password;
	bool isFound = false;
	int sizeC = getClients().getSize();

	while (true) {
		std::cout << "\nPlease enter your username";
		std::cin >> username;
		

		std::cout << "\nPlease enter your password";
		std::cin >> password;
		
		
		
		

		for (int i = 0; i < sizeC; i++) {
			if (getClients()[i].getUsername() == username && getClients()[i].getPassword() == password) {
				indexCurrentClient = i;
				isFound = true;
				break;
			}
		}
		if (!isFound) {
			
			int choice = -1;
			
			std::cout << "Wrong username/password or there is no such account \n";
			std::cout << "If you wish to try again enter 1 \n";
			std::cout << "If you wish to return to previous menu enter 0 \n";
			std::cin >> choice;
			
			if (!choice) {
				return;
			}
			else {
				continue;
			}

		}
		if (isFound) {
			break;
		}
	}
	logedInMenu();

}

void ClientConsole::registerMe() {

	MyString username;
	MyString password;
	MyString firstName;
	MyString lastName;
	Client newClient;
	bool isFound = false;
	int sizeC = getClients().getSize();

	while (true) {
		std::cout << "\nPlease enter your username";
		std::cin >> username;


		for (int i = 0; i < sizeC; i++) {
			if (getClients()[i].getUsername() == username ) {

				isFound = true;
				break;
			}
		}

		if (isFound) {
			std::cout << "Username taken. Please enter a new one\n";
			continue;
		}
		newClient.setUsername(username);
		
		std::cout << "\nPlease enter your password\n";
		std::cin >> password;
		newClient.setPassword(password);

		std::cout << "\nPlease enter your first name\n";
		std::cin >> firstName;
		newClient.setFirstName(firstName);


		std::cout << "\nPlease enter your last name\n";
		std::cin >> lastName;
		newClient.setLastName(lastName);

		indexCurrentClient = getClients().getSize();
		getClients().pushBack(newClient);
		break;
	}
	logedInMenu();
}

const Address& ClientConsole::orderAddress() {
	int x = 0;
	int y = 0;
	Address newAddress;

	std::cout << "\nPlease enter your coordinates\n";
	std::cout << "X: ";
	std::cin >> x;

	std::cout << "Y: ";
	std::cin >> y;

	Point p(x, y);
	newAddress.setPoint(p);

	MyString addressName;
	std::cout << "\nPlease enter your address name\n";
	std::cin >> addressName;
	newAddress.setName(addressName);

	std::cout << "Would you like to add additional information?\nYes - 1\nNo - 0\n";
	int choice = -1;
	std::cin >> choice;
	if (choice) {
		MyString addtionalInfo;
		std::cout << "\nPlease enter the additional information\n";
		std::cin >> addtionalInfo;
		newAddress.setAdditionalInfo(addtionalInfo);
	}
	
}

bool ClientConsole::isDriverFree() {
	int size = getDrivers().getSize();
	
	for (int i = 0; i < size; i++) {
		if (getDrivers()[i].getOrderPointer() == nullptr) {
			return true;
		}
	}
	return false;
}

void ClientConsole::order() {
	if (!isDriverFree()) {
		std::cout << "No free driver. Please try again later.";
		return;
	}
	std::cout << "\nCreate order\n";
	std::cout << "Enter your Address\n";
	Address current = orderAddress();
	std::cout << "Enter your Destination\n";
	Address destination = orderAddress();
	

	getOrderSystem().createOrder(current,destination,indexCurrentClient);
	getClients()[indexCurrentClient].setOrder(getOrderSystem().getOrders()[getOrderSystem().getOrders().getSize() - 1]);

	assignDriver();
}
void ClientConsole::checkOrder() {
	if (getClients()[indexCurrentClient].getOrder().getIsAccepted() == -1) {
		std::cout << "Order has been canceled/denied. Removing order";
		
	}
	if (getClients()[indexCurrentClient].getOrder().getIsAccepted() == 0) {
		std::cout << "Still waiting for a responce from driver";
	}
	if (getClients()[indexCurrentClient].getOrder().getIsAccepted() == 1) {
		std::cout << "Order is accepted. Minutes Left: " << getClients()[indexCurrentClient].getOrder().getMinutesLeft() << "\n";
		std::cout << "Driver info: " << getDrivers()[getClients()[indexCurrentClient].getOrder().getIdDriver()].getFirstName() << " " 
			<< getDrivers()[getClients()[indexCurrentClient].getOrder().getIdDriver()].getLastName() << "\n";
	}
}

void ClientConsole::cancelOrder() {
	if(getClients()[indexCurrentClient].getOrder().getIsAccepted()!=1&& getClients()[indexCurrentClient].getOrder().getIsFinished()!=1)
	getClients()[indexCurrentClient].getOrder().setIsAccepted(-1);
}

void ClientConsole::pay() {
	int toPay = 0;
	int choice = 0;
	if (getClients()[indexCurrentClient].getOrder().getIsPaid()) {
		std::cout << "Order already paid.\n";
		return;
	}
	while (true) {
		
		std::cout << "How much would you like to pay?\n";
		std::cin >> toPay;
		
		if (toPay < 0) {
			std::cout << "Invalid number\n";
			continue;
		}

		if (toPay > getClients()[indexCurrentClient].getBalance()) {
			std::cout << "Insufficient funds. Would you like to add money to your account?\n";
			std::cout << "To add - 1\n";
			std::cout << "Skip action - 0";
			std::cin >> choice;
			if (toPay) {
				add_money();
			}
			else {
				continue;
			}
			
		}

		getClients()[indexCurrentClient].pay(toPay);
	}

	getClients()[indexCurrentClient].getOrder().setCost(toPay);
	getClients()[indexCurrentClient].getOrder().setIsPaid(true);

	
}

void ClientConsole::rate()  {
	if (!getClients()[indexCurrentClient].getOrder().getIsFinished()) {
		std::cout << "The order is still not finished \n";
		return;
	}
	while (true) {
		std::cout << "Rate your driver from 1 to 5. \n";
		int choice = 0;
		std::cin >> choice;
		if (choice < 1 || choice>5) {
			std::cout << "Incorret rating. Please try again";
			continue;
		}
		getClients()[indexCurrentClient].getOrder().setRated(choice);
	}
	//completed order check
}

void ClientConsole::add_money() {
	std::cout << "How much would you like to add?\n";
	int toAdd = 0;
	
	while (true) {
		std::cout << "How much would you like to add?\n";
		std::cin >> toAdd;
		if (toAdd < 0) {
			std::cout << "Invalid number\n";
			continue;
		}
		getClients()[indexCurrentClient].addToBalance(toAdd);
	}
}


void ClientConsole::assignDriver() {
	int size = getDrivers().getSize();
	Point start = getClients()[indexCurrentClient].getOrder().getCurrentAddress().getPoint();
	int indexDriverClosest = -1;
	int minDistance = INT32_MAX;

	for (int i = 0; i < size; i++) {
		if (minDistance > start.getDistance(getDrivers()[i].getAddress().getPoint())) {
			if (getDrivers()[i].getOrderPointer() != nullptr) {
				minDistance = start.getDistance(getDrivers()[i].getAddress().getPoint());
				indexDriverClosest = i;
			}
		}
	}

	getClients()[indexCurrentClient].getOrder().setIdDriver(indexDriverClosest);
	getDrivers()[indexDriverClosest].setOrder(getClients()[indexCurrentClient].getOrder());

}