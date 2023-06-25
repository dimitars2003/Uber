#include "DriverConsole.h"

void DriverConsole::logedInMenu() {
	std::cout << "Hello " << getDrivers()[indexCurrentDriver].getFirstName() << ".\n";
	int choice = -1;
	while (true) {
		std::cout << "\nDriver Menu\n";
		std::cout << "Enter the number of the action you wish to do\n";
		std::cout << "Change Address - 1\n";
		std::cout << "Check messages - 2\n";
		std::cout << "Accept order - 3\n";
		std::cout << "Decline order - 4\n";
		std::cout << "Finish order - 5\n";
		std::cout << "Accept payment - 6\n";
		std::cout << "To log out - 0\n";

		std::cin >> choice;

		if (choice == 0) {

			return;
		}

		if (choice == 1) {
			changeAddress();
		}

		if (choice == 2) {
			check_messages();
		}

		if (choice == 3) {
			acceptOrder();
		}

		if (choice == 4) {
			declineOrder();
		}

		if (choice == 5) {
			finishOrder();
		}

		if (choice == 6) {
			acceptPayment();
		}

	}
}

DriverConsole::DriverConsole() : ConsoleBase() {

}

void DriverConsole::login() {

	MyString username;
	MyString password;
	bool isFound = false;
	int sizeD = getDrivers().getSize();

	while (true) {
		std::cout << "\nPlease enter your username\n";
		std::cin >> username;


		std::cout << "\nPlease enter your password\n";
		std::cin >> password;





		for (int i = 0; i < sizeD; i++) {
			if (getDrivers()[i].getUsername() == username && getDrivers()[i].getPassword() == password) {
				indexCurrentDriver = i;
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

void DriverConsole::registerMe() {
	MyString username;
	MyString password;
	MyString firstName;
	MyString lastName;
	MyString number;
	MyString carNumber;
	Address newAddress;

	int x = 0;
	int y = 0;
	bool isFound = false;
	int sizeD = getDrivers().getSize();

	while (true) {
		std::cout << "\nPlease enter your username";
		std::cin >> username;


		for (int i = 0; i < sizeD; i++) {
			if (getDrivers()[i].getUsername() == username) {

				isFound = true;
				break;
			}
		}

		if (isFound) {
			std::cout << "Username taken. Please enter a new one\n";
			continue;
		}

		std::cout << "\nPlease enter your password\n";
		std::cin >> password;

		std::cout << "\nPlease enter your first name\n";
		std::cin >> firstName;


		std::cout << "\nPlease enter your last name\n";
		std::cin >> lastName;

		std::cout << "\nPlease enter your number\n";
		std::cin >> number;

		std::cout << "\nPlease enter your car number\n";
		std::cin >> carNumber;

		std::cout << "\nPlease enter your coordinates\n";
		std::cout << "X: ";
		std::cin >> x;

		std::cout << "Y: ";
		std::cin >> y;

		Point p(x, y);
		newAddress.setPoint(p);

		
		std::cout << "\nPlease enter your address name\n";
		char bufferAddressName[1024]{ "" };
		std::cin.getline(bufferAddressName, 1024);
		MyString addressName(bufferAddressName);
		newAddress.setName(addressName);

		std::cout << "Would you like to add additional information?\nYes - 1\nNo - 0\n";
		int choice = -1;
		std::cin >> choice;
		if (choice) {
			
			std::cout << "\nPlease enter the additional information\n";
			char bufferAdditionalAddress[1024]{""};
			std::cin.getline(bufferAdditionalAddress, 1024);
			MyString addtionalInfo (bufferAdditionalAddress);
			newAddress.setAdditionalInfo(addtionalInfo);
		}


		Driver newDriver(username, password, firstName, lastName, number, carNumber, newAddress);

		indexCurrentDriver = getDrivers().getSize();
		getDrivers().pushBack(newDriver);
		break;
	}
	logedInMenu();
}

void DriverConsole::changeAddress() {
	Address newAddress;
	int x = 0;
	int y = 0;

	std::cout << "\nPlease enter your coordinates\n";
	std::cout << "X: ";
	std::cin >> x;

	std::cout << "Y: ";
	std::cin >> y;

	Point p(x, y);
	newAddress.setPoint(p);

	
	
	char bufferAddressName[1024]{""};
	std::cout << "\nPlease enter your address name\n";
	std::cin.ignore();
	std::cin.getline(bufferAddressName, 1024);

	MyString addressName(bufferAddressName);
	
	newAddress.setName(addressName);

	std::cout << "Would you like to add additional information?\nYes - 1\nNo - 0\n";
	int choice = -1;
	std::cin >> choice;
	if (choice) {
		
		std::cout << "\nPlease enter the additional information\n";
		
		char bufferAdditionalAddress[1024]{ "" };
		std::cin.ignore();
		std::cin.getline(bufferAdditionalAddress, 1024);
		MyString addtionalInfo(bufferAdditionalAddress);
		newAddress.setAdditionalInfo(addtionalInfo);
	}
	getDrivers()[indexCurrentDriver].setAddress(newAddress);
}

void DriverConsole::check_messages() {
	if (getDrivers()[indexCurrentDriver].getOrderPointer() == nullptr) {
		std::cout << "\nNo orders. \n";
	}
	
	if (getDrivers()[indexCurrentDriver].getOrderPointer() != nullptr) {
		if (getDrivers()[indexCurrentDriver].getOrder().isOrderCompleted()) {
			getDrivers()[indexCurrentDriver].removeOrder();
			check_messages();
			return;
		}
		if (getDrivers()[indexCurrentDriver].getOrder().getIsAccepted() != -1) {
			std::cout << "\nYou have an order. \n";
			std::cout << "From " << getDrivers()[indexCurrentDriver].getOrder().getCurrentAddress().getName() << " to " << getDrivers()[indexCurrentDriver].getOrder().getDestination().getName();

		}
	}
}

void DriverConsole::acceptOrder() {
	if (getDrivers()[indexCurrentDriver].getOrderPointer() == nullptr) {
		std::cout << "\nNo order to accept\n";
		return;
	}

	if (getDrivers()[indexCurrentDriver].getOrder().getIsAccepted() == 1) {
		std::cout << "\nOrder has already been accepted.\n";
	}

	if (getDrivers()[indexCurrentDriver].getOrder().getIsAccepted() == 0) {
		while (true) {
			
			std::cout << "\nHow many minutes to arrival\n";
			int minutes = 0;
			std::cin >> minutes;
			
			if (minutes < 0) {
				std::cout << "Invalid input. Please enter again";
				continue;
			}

			getDrivers()[indexCurrentDriver].getOrder().setMinutesLeft(minutes);
			getDrivers()[indexCurrentDriver].getOrder().setIsAccepted(1);
			return;
		}
	}
	if (getDrivers()[indexCurrentDriver].getOrder().getIsAccepted() == -1) {
		getDrivers()[indexCurrentDriver].removeOrder();
		acceptOrder();
		return;
	}
}

void DriverConsole::declineOrder() {
	if (getDrivers()[indexCurrentDriver].getOrderPointer() == nullptr) {
		std::cout << "\nNo order to decline\n";
		return;
	}
	
	if (getDrivers()[indexCurrentDriver].getOrder().getIsAccepted() == -1) {
		getDrivers()[indexCurrentDriver].removeOrder();
		declineOrder();
		return;
	}

	if (getDrivers()[indexCurrentDriver].getOrder().isOrderCompleted()) {
		getDrivers()[indexCurrentDriver].removeOrder();
		declineOrder();
		return;
	}

	if (getDrivers()[indexCurrentDriver].getOrder().getIsAccepted() == 1) {
		std::cout << "\nOrder already accepted\n";
		
		return;
	}

	if (getDrivers()[indexCurrentDriver].getOrder().getIsAccepted() == 0) {
		getDrivers()[indexCurrentDriver].getOrder().setIsAccepted(-1);
		getDrivers()[indexCurrentDriver].removeOrder();
		return;
	}
	
}

void DriverConsole::finishOrder() {
	if (getDrivers()[indexCurrentDriver].getOrderPointer() == nullptr) {
		std::cout << "\nNo order to finish\n";
		return;
	}

	if (getDrivers()[indexCurrentDriver].getOrder().getIsAccepted() == 1) {
		getDrivers()[indexCurrentDriver].getOrder().setIsFinished(true);
		std::cout << "\nOrder has been finished. Waiting for payment.\n";

	}
	else {
		std::cout << "\nNo accepted order to be finished.\n";
	}
	return;
}

void DriverConsole::acceptPayment() {
	if (getDrivers()[indexCurrentDriver].getOrderPointer() == nullptr) {
		std::cout << "\nNo payment to be recieved\n";
		return;
	}

	if (getDrivers()[indexCurrentDriver].getOrder().getIsFinished() && getDrivers()[indexCurrentDriver].getOrder().getIsPaid()) {
		getDrivers()[indexCurrentDriver].getOrder().setPaymentRecieved(true);
		getDrivers()[indexCurrentDriver].addToBalance(getDrivers()[indexCurrentDriver].getOrder().getCost());
		std::cout << "\nPayment accepted.\n";

	}
	else {
		std::cout << "\nOrder not finished or still waiting to be paid.\n";
	}
	if (getDrivers()[indexCurrentDriver].getOrder().isOrderCompleted()) {
		getDrivers()[indexCurrentDriver].removeOrder();
	}
}
