#include "Client.h"

Client::Client() : User() {

}
Client::Client(MyString username, MyString password, MyString firstName, MyString lastName) : User(username, password, firstName, lastName){

}



void Client::pay(int toPay) {
	if (toPay > 0) {
		setBalance(getBalance() - toPay);
	}
}

void Client::setOrder( Order& order) {
	this->order = &order;
}

 Order& Client::getOrder()  {
	return *(this->order);
}

const Order* Client::getOrderPointer() const {
	return order;
}

void Client::removeOrder() {
	order = nullptr;
}