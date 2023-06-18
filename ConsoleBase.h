#pragma once
#include "Vector.hpp"
#include "Client.h"
#include "Driver.h"
#include "OrderSystem.h"

class ConsoleBase {
private:
	//helper
	int getFileSize(std::ifstream& in) const;
	char* getBeforeComma(MyString& other);

	void readClients(std::ifstream& in);
	void readDrivers(std::ifstream& in);
	
	void writeClients(std::ofstream& out);
	void writeDrivers(std::ofstream& out);
	
	Vector<Client> clients;
	Vector<Driver> drivers;
	OrderSystem orders;

	void connectOrders();

public:
	
	ConsoleBase();
	virtual void login() = 0;
	
	virtual void registerMe() = 0;
	virtual ~ConsoleBase();



	Vector<Client>& getClients();
	Vector<Driver>& getDrivers();

	OrderSystem& getOrderSystem();

};