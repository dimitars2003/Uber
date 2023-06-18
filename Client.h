#pragma once
#include "User.h"
#include "Order.h"

class Client : public User {
private:

	Order* order = nullptr;

public:
	
	Client();
	Client(MyString username, MyString password, MyString firstName, MyString lastName);
	
	void removeOrder();

	~Client()=default;

	void setOrder( Order& order);
	 Order& getOrder() ;
	const Order* getOrderPointer() const;

	void pay(int toPay);


};
