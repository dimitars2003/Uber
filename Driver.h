#pragma once
#include "User.h"
#include "Address.h"
#include "Order.h"

class Driver : public User {
private:
	MyString number;
	MyString carNumber;
	Address currentAddress;
	
	Order* order = nullptr;

public:

	Driver();
	Driver(MyString username, MyString password, MyString firstName, MyString lastName, MyString number, MyString carNumber, Address currentAddress);
	
	~Driver() = default;

	void setNumber(const MyString& number);
	void setCarNumber(const MyString& carNumber);
	void setAddress(const Address& address);
	
	const MyString& getNumber() const;
	const MyString& getCarNumber() const;
	const Address& getAddress() const;
	
	void setOrder(Order& order);
	const Order& getOrder() const;
	const Order* getOrderPointer() const;

};