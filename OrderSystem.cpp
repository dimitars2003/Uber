#include "OrderSystem.h"
#include <fstream>
#include <sstream>

char* OrderSystem::getBeforeComma(MyString& other) {

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

int OrderSystem::charToInt(MyString& line) {
	int toReturn = 0;
	char* charToInt = getBeforeComma(line);
	std::stringstream ssR;
	ssR << charToInt;
	ssR >> toReturn;
	return toReturn;
	
}

const Address& OrderSystem::addressMake(MyString& line) {
	Address toReturn;
	int x = charToInt(line);;
	int y = charToInt(line);;

	
	
	Point p(x, y);
	toReturn.setPoint(p);

	toReturn.setName(getBeforeComma(line));

	if (getBeforeComma(line)[0] != '\0') {
		toReturn.setAdditionalInfo(getBeforeComma(line));
	}

	return toReturn;
}

OrderSystem::OrderSystem() : orders() {
	std::ifstream in("Order.txt", std::ios::in);
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
	Order toPush;
	for (int i = 0; i < counter; i++) {

		

		toPush.setCurrentAddress(addressMake(lines[i]));

		

		toPush.setDestination(addressMake(lines[i]));

		
		toPush.setCost(charToInt(lines[i]));

		toPush.setMinutesLeft(charToInt(lines[i]));

		toPush.setIdClient(charToInt(lines[i]));

		
		toPush.setIdDriver(charToInt(lines[i]));

		
		toPush.setIsAccepted(charToInt(lines[i]));

		toPush.setRated(charToInt(lines[i]));


		toPush.setIsFinished(charToInt(lines[i]));

		
		toPush.setIsPaid(charToInt(lines[i]));

		toPush.setPaymentRecieved(charToInt(lines[i]));
		
		orders.pushBack(toPush);

		std::cout << orders[i].getCurrentAddress().getPoint().getX() << "," << orders[i].getCurrentAddress().getPoint().getY() << "," << orders[i].getCurrentAddress().getName()
			<< "," << orders[i].getCurrentAddress().getAdditionalInfo() << "," << orders[i].getDestination().getPoint().getX() << ","
			<< orders[i].getDestination().getPoint().getY() << "," << orders[i].getDestination().getName() << "," << orders[i].getDestination().getAdditionalInfo()
			<< "," << orders[i].getCost() << "," << orders[i].getMinutesLeft() << "," << orders[i].getIdClient() << "," << orders[i].getIdDriver() << "," 
			<< orders[i].getIsAccepted() << "," << orders[i].getRated() << "," << orders[i].getIsFinished() << "," << orders[i].getIsPaid() 
			<<"," << orders[i].getPaymentRecieved() << "\n";
	}
}

 Vector<Order>& OrderSystem::getOrders()  {
	return orders;
}

OrderSystem::~OrderSystem() {
	
	std::ofstream out("Order.txt", std::ios::out | std::ios::trunc);
	
	if (!out.is_open()) {
		std::cout << "File error!" << std::endl;
		return;
	}
	for (int i = 0; i < orders.getSize(); i++) {
		out << orders[i].getCurrentAddress().getPoint().getX() << ",";
		out << orders[i].getCurrentAddress().getPoint().getY() << ",";
		out << orders[i].getCurrentAddress().getName() << ",";
		out << orders[i].getCurrentAddress().getAdditionalInfo() << ",";

		out << orders[i].getDestination().getPoint().getX() << ",";
		out << orders[i].getDestination().getPoint().getY() << ",";
		out << orders[i].getDestination().getName() << ",";
		out << orders[i].getDestination().getAdditionalInfo() << ",";

		out << orders[i].getCost() << ",";
		out << orders[i].getMinutesLeft() << ",";
		out << orders[i].getIdClient() << ",";
		out << orders[i].getIdDriver() << ",";
		out << orders[i].getIsAccepted() << ",";
		out << orders[i].getRated() << ",";
		out << orders[i].getIsFinished() << ",";
		out << orders[i].getIsPaid() << ",";
		out << orders[i].getPaymentRecieved() << "\n";
		
	}
}

void OrderSystem::createOrder(const Address& currentAddress, const Address& destination, int clientId) {
	
	Order newOrder( currentAddress,  destination, clientId);

	orders.pushBack(newOrder);	
}
