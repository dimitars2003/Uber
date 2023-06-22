#pragma once
#include "Vector.hpp"
#include "Order.h"

class OrderSystem {
private:
	Vector<Order> orders;
	char* getBeforeComma(MyString& other);
	int charToInt(MyString& line);
	const Address& addressMake(MyString& line);
	
	void writeToFile();
	void spaceParser(const MyString& toParse, std::ostream& out);
	void readFromFile();
	void print(int index) const;

public:
	OrderSystem();

	 Vector<Order>& getOrders() ;

	~OrderSystem();

	void createOrder(const Address& currentAddress, const Address& destination, int clientId );

};