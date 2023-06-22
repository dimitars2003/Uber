#pragma once
#include "Vector.hpp"
#include "Client.h"
#include "Driver.h"
#include "OrderSystem.h"

class ConsoleBase {
private:
	
	char* getBeforeComma(MyString& other);

	void readClients(std::ifstream& in);
	void readDrivers(std::ifstream& in);
	
	void writeClients(std::ofstream& out);
	void writeDrivers(std::ofstream& out);
	
	Vector<Client> clients;
	Vector<Driver> drivers;
	OrderSystem orders;

	void connectOrders();

	void printDriver(int i);
	void printClient(int i);

	void spaceParser(const MyString& toParse, std::ostream&);
public:
	
	ConsoleBase();
	virtual void login() = 0;
	
	virtual void registerMe() = 0;
	virtual ~ConsoleBase();



	Vector<Client>& getClients();
	Vector<Driver>& getDrivers();

	OrderSystem& getOrderSystem();

};