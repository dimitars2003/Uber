#include "ConsoleBase.h"
#include <fstream>
#include <iostream>
#include <sstream>


int ConsoleBase::getFileSize(std::ifstream& in) const {//delete
	size_t current = in.tellg();
	in.seekg(0, std::ios::end);
	size_t size = in.tellg();
	in.seekg(current, std::ios::beg);

	return size;
}

char* ConsoleBase::getBeforeComma(MyString& other) {

	int size = other.length();
	char* buffer = new char[size];


	for (int i = 0; i < size; i++) {
		if (other[i] == ',') {

			buffer[i] = '\0';
			other = other.substr(i, static_cast<size_t>(size) - i);
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

	while (!in.eof()) {

		char buffer[1024];
		in.getline(buffer, 1024);
		lines[counter] = buffer;
		counter++;
	}
	MyString line;
	Client toPush;
	for (int i = 0; i < counter; i++) {

		toPush.setFirstName(getBeforeComma(lines[i]));
		toPush.setLastName(getBeforeComma(lines[i]));
		toPush.setUsername(getBeforeComma(lines[i]));
		toPush.setPassword(getBeforeComma(lines[i]));
		
		std::stringstream ss(getBeforeComma(lines[i]));
		int balance;
		ss >> balance;
		toPush.setBalance(balance);
		
		clients.pushBack(toPush);
		std::cout << clients[i].getFirstName() << "," << clients[i].getLastName() << "," << clients[i].getPassword() << "," << clients[i].getUsername()
			<< "," << clients[i].getBalance() << std::endl;
	}
}


void ConsoleBase::readDrivers(std::ifstream& in) {
	if (!in.is_open()) {
		std::cout << "File error";
		return;
	}
	int counter = 0;
	Vector<MyString> lines;

	while (!in.eof()) {

		char buffer[1024];
		in.getline(buffer, 1024);
		lines[counter] = buffer;
		counter++;
	}

	
	Driver toPush;
	int balance;
	Address driverAddress;
	int x;
	int y;
	
	for (int i = 0; i < counter; i++) {

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

		if (getBeforeComma(lines[i])[0] != '\0') {
			driverAddress.setAdditionalInfo(getBeforeComma(lines[i]));
		}

		toPush.setAddress(driverAddress);
		
		drivers.pushBack(toPush);

		std::cout << drivers[i].getFirstName() << "," << drivers[i].getLastName() << "," << drivers[i].getPassword() << "," << drivers[i].getUsername() << "," 
			<< drivers[i].getBalance() << "," << drivers[i].getNumber() << "," << drivers[i].getCarNumber() << "," << drivers[i].getAddress().getPoint().getX()
			<< "," << drivers[i].getAddress().getPoint().getY()	<< "," << drivers[i].getAddress().getName() << "," << drivers[i].getAddress().getAdditionalInfo() << std::endl;
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
		out << clients[i].getBalance() << "\n";

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
		out << drivers[i].getAddress().getName() << ",";
		out << drivers[i].getAddress().getAdditionalInfo() << "\n";


	}
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