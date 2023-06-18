#pragma once
#include "Vector.hpp"
#include "Order.h"

class OrderSystem {
private:
	Vector<Order> orders;
	char* getBeforeComma(MyString& other);
	int charToInt(MyString& line);
	const Address& addressMake(MyString& line);
	

public:
	OrderSystem();

	 Vector<Order>& getOrders() ;

	~OrderSystem();

	void createOrder(const Address& currentAddress, const Address& destination, int clientId );

};