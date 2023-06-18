#include "Driver.h"

Driver::Driver() : User(), number(), carNumber(), currentAddress(){

}
Driver::Driver(MyString username, MyString password, MyString firstName, MyString lastName, MyString number, MyString carNumber, Address currentAddress) : 
	User(username, password, firstName, lastName), number(number), carNumber(carNumber), currentAddress(currentAddress) {

}

void Driver::setNumber(const MyString& number) {
	this->number = number;
}
void Driver::setCarNumber(const MyString& carNumber) {
	this->carNumber = carNumber;
}
void Driver::setAddress(const Address& address) {
	this->currentAddress = address;
}

const MyString& Driver::getNumber() const {
	return number;
}
const MyString& Driver::getCarNumber() const {
	return carNumber;
}
const Address& Driver::getAddress() const {
	return currentAddress;
}

void Driver::setOrder(Order& order) {
	this->order = &order;
}

 Order& Driver::getOrder()  {
	return *(this->order);
}

const Order* Driver::getOrderPointer() const {
	return order;
}


void Driver::removeOrder() {
	order = nullptr;
}
