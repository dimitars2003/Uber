#include "ConsoleBase.h"
#include <fstream>
#include <iostream>
#include <sstream>




char* ConsoleBase::getBeforeComma(MyString& other) {

	int size = other.length();
	
	char* buffer = new char[size];

	size_t temp;
	for (int i = 0; i < size; i++) {
		if (other[i] == ',') {

			buffer[i] = '\0';
			temp = size - i;

			other = other.substr(i+1, temp-1);
			
			
			return buffer;
		}
		buffer[i] = other[i];

	}
}

void ConsoleBase::readClients(std::ifstream& in) {
	if (!in.is_open()) {
		std::cout << "File error";
		return;
	}
	int counter = 0;
	Vector<MyString> lines;
	std::cout << "Clients\n";
	while (!in.eof()) {

		char buffer[1024];
		in.getline(buffer, 1024);
		lines.pushBack (buffer);
		counter++;
	}
	MyString line;
	Client toPush;
	for (int i = 0; i < counter; i++) {

		if (lines[i].length() == 0) {
			continue;
		}

		toPush.setFirstName(getBeforeComma(lines[i]));
		toPush.setLastName(getBeforeComma(lines[i]));
		
		toPush.setUsername(getBeforeComma(lines[i]));
		toPush.setPassword(getBeforeComma(lines[i]));
		
		std::stringstream ss(getBeforeComma(lines[i]));
		
		int balance;
		ss >> balance;
		toPush.setBalance(balance);
		
		clients.pushBack(toPush);

		printClient(i);
	}
}


void ConsoleBase::readDrivers(std::ifstream& in) {
	if (!in.is_open()) {
		std::cout << "File error";
		return;
	}
	int counter = 0;
	Vector<MyString> lines;
	std::cout << "Drivers\n";
	while (!in.eof()) {

		char buffer[1024];
		in.getline(buffer, 1024);
		lines.pushBack(buffer);
		counter++;
	}

	
	Driver toPush;
	int balance;
	Address driverAddress;
	int x;
	int y;
	
	for (int i = 0; i < counter; i++) {

		if (lines[i].length() == 0) {
			continue;
		}

		toPush.setFirstName(getBeforeComma(lines[i]));
		toPush.setLastName(getBeforeComma(lines[i]));
		toPush.setUsername(getBeforeComma(lines[i]));
		toPush.setPassword(getBeforeComma(lines[i]));
		
		std::stringstream ss(getBeforeComma(lines[i]));
		ss >> balance;
		toPush.setBalance(balance);
		
		toPush.setNumber(getBeforeComma(lines[i]));
		toPush.setCarNumber(getBeforeComma(lines[i]));

		
		char* xToInt = getBeforeComma(lines[i]);
		char* yToInt = getBeforeComma(lines[i]);
		std::stringstream ssP;
		ssP << xToInt << ' ' << yToInt;
		ssP >> x >> y;
		Point p(x, y);
		driverAddress.setPoint(p);

		driverAddress.setName(getBeforeComma(lines[i]));
		
		MyString additionalInfoCheck(getBeforeComma(lines[i]));
		
		if (additionalInfoCheck[0] != '\0') {
			
			driverAddress.setAdditionalInfo(additionalInfoCheck);
		}
		else {
			driverAddress.setAdditionalInfo("\0");
		}

		toPush.setAddress(driverAddress);
		
		drivers.pushBack(toPush);

		printDriver(i);
	}
}

void ConsoleBase:: connectOrders() {
	int size = orders.getOrders().getSize();
	for (int i = 0; i < size; i++) {
		if (!orders.getOrders()[i].isOrderCompleted()) {
			
			if (clients[orders.getOrders()[i].getIdClient()].getOrderPointer() != nullptr);
			clients[orders.getOrders()[i].getIdClient()].setOrder(orders.getOrders()[i]);

			if (drivers[orders.getOrders()[i].getIdClient()].getOrderPointer() != nullptr);
			drivers[orders.getOrders()[i].getIdDriver()].setOrder(orders.getOrders()[i]);
		}
	}
}

ConsoleBase::ConsoleBase() : clients(), drivers() , orders(){
	


	std::ifstream inC("Client.txt", std::ios::in);

	readClients(inC);
	inC.close();
	
	std::ifstream inD("Driver.txt", std::ios::in);

	readDrivers(inD);
	inD.close();

	
}

void ConsoleBase::writeClients(std::ofstream& out) {
	if (!out.is_open()) {
		std::cout << "Error!" << std::endl;
		return;
	}
	for (int i = 0; i < clients.getSize(); i++) {
		out << clients[i].getFirstName() << ",";
		out << clients[i].getLastName() << ",";
		out << clients[i].getUsername() << ",";
		out << clients[i].getPassword() << ",";
		out << clients[i].getBalance() << ",\n";

	}
}
void ConsoleBase::writeDrivers(std::ofstream& out) {
	if (!out.is_open()) {
		std::cout << "File error!" << std::endl;
		return;
	}

	for (int i = 0; i < drivers.getSize(); i++) {

		out << drivers[i].getFirstName() << ",";
		out << drivers[i].getLastName() << ",";
		out << drivers[i].getUsername() << ",";
		out << drivers[i].getPassword() << ",";
		out << drivers[i].getBalance() << ",";

		out << drivers[i].getNumber() << ",";
		out << drivers[i].getCarNumber() << ",";

		out << drivers[i].getAddress().getPoint().getX() << ",";
		out << drivers[i].getAddress().getPoint().getY() << ",";
		
		if(!drivers[i].getAddress().getName().hasSpace())
			out << drivers[i].getAddress().getName() << ",";
		else {
			spaceParser(drivers[i].getAddress().getName(), out);
			out << ",";
		}
		
		
		if (!drivers[i].getAddress().getAdditionalInfo().hasSpace())
			out << drivers[i].getAddress().getAdditionalInfo() << ",\n";
		else {
			spaceParser(drivers[i].getAddress().getAdditionalInfo(), out);
			out << ",";
			out << "\n";
		}
	}
}

void ConsoleBase::spaceParser(const MyString& toParse, std::ostream& out) {
	for (int i = 0; i < toParse.length(); i++) {
		if (toParse[i] == ' ') {
			out << " ";
		}
		else {
			out << toParse[i];
		}
	}
	return;
}

ConsoleBase::~ConsoleBase() {
	//write changes to files
	
	std::ofstream outC("Client.txt", std::ios::out| std::ios::trunc);//check for more if needed
	writeClients(outC);
	outC.close();

	std::ofstream outD("Driver.txt", std::ios::out | std::ios::trunc);//check for more if needed
	writeDrivers(outD);
	outD.close();
	
	//write Orders
}


Vector<Client>& ConsoleBase::getClients()  {
	return clients;
}

Vector<Driver>& ConsoleBase::getDrivers()  {
	return drivers;
}

 OrderSystem& ConsoleBase::getOrderSystem() {
	return orders;
}


 void ConsoleBase::printDriver(int i) {
	 std::cout << drivers[i].getFirstName() << "," << drivers[i].getLastName()  << "," << drivers[i].getUsername() << ","  << drivers[i].getPassword() << ","
		 << drivers[i].getBalance() << "," << drivers[i].getNumber() << "," << drivers[i].getCarNumber() << "," << drivers[i].getAddress().getPoint().getX()
		 << "," << drivers[i].getAddress().getPoint().getY() << "," << drivers[i].getAddress().getName() << "," << drivers[i].getAddress().getAdditionalInfo() << std::endl;
 }
 void ConsoleBase::printClient(int i) {
	 
	 std::cout << clients[i].getFirstName() << "," << clients[i].getLastName()  << "," << clients[i].getUsername() << "," << clients[i].getPassword()
		 << "," << clients[i].getBalance() << std::endl;
 }