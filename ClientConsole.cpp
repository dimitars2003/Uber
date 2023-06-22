#include "ClientConsole.h"
#include <fstream>
#include <iostream>


void ClientConsole::logedInMenu()  {

	std::cout << "\nHello " << getClients()[indexCurrentClient].getFirstName()<<".\n";
	int choice = -1;
	while (true) {
		std::cout << "\nClient Menu\n";
		std::cout << "Current Balance: " << getClients()[indexCurrentClient].getBalance() << "\n";
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
		std::cout << "\nPlease enter your username\n";
		std::cin >> username;
		

		std::cout << "\nPlease enter your password\n";
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

	char bufferAddressName[1024]{ "" };
	std::cout << "\nPlease enter your address name\n";
	std::cin.ignore();
	std::cin.getline(bufferAddressName, 1024);
	
	MyString addressName(bufferAddressName);
	newAddress.setName(addressName);

	std::cout << "Would you like to add additional information?\nYes - 1\nNo - 0\n";
	int choice = -1;
	std::cin >> choice;
	if (choice) {

		char bufferAdditionalAddress[1024]{ "" };
		std::cin.ignore();
		std::cin.getline(bufferAdditionalAddress, 1024);
		
		MyString addtionalInfo(bufferAdditionalAddress);
		newAddress.setAdditionalInfo(addtionalInfo);
	}
	return newAddress;

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
	
	if (getClients()[indexCurrentClient].getOrderPointer() == nullptr) {



		if (!isDriverFree()) {
			std::cout << "No free driver. Please try again later.";
			return;
		}
		std::cout << "\nCreate order\n";
		std::cout << "Enter your Address\n";
		Address current = orderAddress();
		std::cout << "Enter your Destination\n";
		Address destination = orderAddress();


		getOrderSystem().createOrder(current, destination, indexCurrentClient);
		getClients()[indexCurrentClient].setOrder(getOrderSystem().getOrders()[getOrderSystem().getOrders().getSize() - 1]);

		assignDriver();
	}
	else if (getClients()[indexCurrentClient].getOrder().isOrderCompleted()) {
		getClients()[indexCurrentClient].removeOrder();
		order();
	}
	else {
		std::cout << "You already have an order. To make a new order, please cancel the previous one." << std::endl;
	}
}
void ClientConsole::checkOrder() {
	if (getClients()[indexCurrentClient].getOrderPointer() == nullptr) {
		std::cout << "No orders. \n";
		return;
	}
	if (getClients()[indexCurrentClient].getOrder().isOrderCompleted()) {
		getClients()[indexCurrentClient].removeOrder();
		checkOrder();
		return;
	}
	if (getClients()[indexCurrentClient].getOrder().getIsAccepted() == -1) {
		std::cout << "Order has been canceled/denied. Removing order";
		int size = getOrderSystem().getOrders().getSize();
		for (int i = 0; i < size; i++) {
			if (&getOrderSystem().getOrders()[i] == getClients()[indexCurrentClient].getOrderPointer()) {
				getOrderSystem().getOrders().popAt(i);
				getClients()[indexCurrentClient].removeOrder();
			}
		}
		return;
	}
	if (getClients()[indexCurrentClient].getOrder().getIsAccepted() == 0) {
		std::cout << "Still waiting for a responce from driver";
		return;
	}
	if (getClients()[indexCurrentClient].getOrder().getIsAccepted() == 1) {
		std::cout << "Order is accepted. Minutes Left: " << getClients()[indexCurrentClient].getOrder().getMinutesLeft() << "\n";
		std::cout << "Driver info: " << getDrivers()[getClients()[indexCurrentClient].getOrder().getIdDriver()].getFirstName() << " " 
			<< getDrivers()[getClients()[indexCurrentClient].getOrder().getIdDriver()].getLastName() << "\n";
		return;
	}
}

void ClientConsole::cancelOrder() {
	if (getClients()[indexCurrentClient].getOrderPointer() == nullptr) {
		std::cout << "\nNo order to cancel. \n";
		return;
	}

	if (getClients()[indexCurrentClient].getOrder().isOrderCompleted()) {
		getClients()[indexCurrentClient].removeOrder();
		cancelOrder();
	}
	
	if (getClients()[indexCurrentClient].getOrder().getIsAccepted() != 1 && getClients()[indexCurrentClient].getOrder().getIsFinished() != 1) {
		getClients()[indexCurrentClient].getOrder().setIsAccepted(-1);
		getClients()[indexCurrentClient].removeOrder();
	}
	return;
}

void ClientConsole::pay() {
	if (getClients()[indexCurrentClient].getOrderPointer() == nullptr) {
		std::cout << "\nNo order to pay. \n";
		return;
	}
	
	if (getClients()[indexCurrentClient].getOrder().getIsPaid()) {
		std::cout << "Order is already paid.\n";
		return;
	}

	if (!getClients()[indexCurrentClient].getOrder().getIsFinished()) {
		std::cout << "Order is not finished\n";
		return;
	}

	if (!getClients()[indexCurrentClient].getOrder().getIsAccepted()) {
		std::cout << "Order is still waiting for a driver responce\n";
		return;
	}
	if (getClients()[indexCurrentClient].getOrder().getIsAccepted()==-1) {
		std::cout << "Order is canceled/declined\n";
		getClients()[indexCurrentClient].removeOrder();
		return;
	}

	int toPay = 0;
	int choice = 0;
	
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

	if (getClients()[indexCurrentClient].getOrder().isOrderCompleted()) {
		getClients()[indexCurrentClient].removeOrder();
	}
	return;
}

void ClientConsole::rate()  {
	
	if (getClients()[indexCurrentClient].getOrderPointer() == nullptr) {
		std::cout << "No order to rate.\n";
		return;
	}

	if (getClients()[indexCurrentClient].getOrder().getRated()) {
		std::cout << "Order is already paid.\n";
		return;
	}

	if (!getClients()[indexCurrentClient].getOrder().getIsFinished()) {
		std::cout << "The order is still not finished \n";
		return;
	}
	
	if (!getClients()[indexCurrentClient].getOrder().getIsAccepted()) {
		std::cout << "Order is still waiting for a driver responce\n";
		return;
	}
	
	if (getClients()[indexCurrentClient].getOrder().getIsAccepted() == -1) {
		std::cout << "Order is canceled/declined\n";
		getClients()[indexCurrentClient].removeOrder();
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
	if (getClients()[indexCurrentClient].getOrder().isOrderCompleted()) {
		getClients()[indexCurrentClient].removeOrder();
	}
	return;
}

void ClientConsole::add_money() {
	
	int toAdd = 0;
	
	while (true) {
		std::cout << "How much would you like to add?\n";
		std::cin >> toAdd;
		if (toAdd < 0) {
			std::cout << "Invalid number\n";
			continue;
		}
		getClients()[indexCurrentClient].addToBalance(toAdd);
		break;
	}
	return;
}


void ClientConsole::assignDriver() {
	int size = getDrivers().getSize();
	Point start = getClients()[indexCurrentClient].getOrder().getCurrentAddress().getPoint();
	int indexDriverClosest = -1;
	int minDistance = INT32_MAX;

	for (int i = 0; i < size; i++) {
		if (minDistance > start.getDistance(getDrivers()[i].getAddress().getPoint())) {
			if (getDrivers()[i].getOrderPointer() == nullptr) {
				minDistance = start.getDistance(getDrivers()[i].getAddress().getPoint());
				indexDriverClosest = i;
			}
		}
	}

	getClients()[indexCurrentClient].getOrder().setIdDriver(indexDriverClosest);
	getDrivers()[indexDriverClosest].setOrder(getClients()[indexCurrentClient].getOrder());
	return;
}