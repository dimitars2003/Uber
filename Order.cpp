#include "Order.h"


Order::Order(Address current, Address destination, int idClient) {
	this->currentAddress = current;
	this->destination = destination;
	this->idClient = idClient;
}

void Order::setCurrentAddress(const Address& current) {
	this->currentAddress = current;

}

void Order::setDestination(const Address& destination) {
	this->destination = destination;
}

void Order::setCost(int cost) {
	this->cost = cost;
}

void Order::setIdClient(int idClient) {
	this->idClient = idClient;
}

void Order::setIdDriver(int idDriver) {
	this->idDriver = idDriver;
}

void Order::setIsAccepted(int isAccepted) {
	this->isAccepted = isAccepted;
}

void Order::setIsFinished(bool isFinished) {
	this->isFinished = isFinished;
}

void Order::setIsPaid(bool isPaid) {
	this->isPaid = isPaid;
}

void Order::setRated(int rated) {
	this->rating = rated;
}


const Address& Order::getCurrentAddress() const {
	return currentAddress;
}

const Address& Order::getDestination() const {
	return destination;
}

const int Order::getCost() const {
	return cost;
}

const int Order::getIdClient() const {
	return idClient;
}

const int Order::getIdDriver() const {
	return idDriver;
}

const int Order::getIsAccepted() const {
	return isAccepted;
}

const bool Order::getIsFinished() const {
	return isFinished;
}

const bool Order::getIsPaid() const {
	return isPaid;
}

const int Order::getRated() const {
	return rating;
}

const bool Order::getPaymentRecieved() const {
	return isPaymentRecieved;
}

void Order::setPaymentRecieved(bool isPaymentRecieved) {
	this->isPaymentRecieved = isPaymentRecieved;
}

const int Order::getMinutesLeft() const {
	return minutesLeft;
}

void Order::setMinutesLeft(int minutesLeft) {
	this->minutesLeft = minutesLeft;
}

bool Order::isOrderCompleted() const {
	return isOrderAccepted() && isFinished && isPaid && isRated() && isPaymentRecieved;
}
bool Order::isOrderDeclined() const {
	return isAccepted == -1;
}
bool Order::isOrderAccepted() const {
	return isAccepted == 1;
}

bool Order::isRated() const {
	return rating;
}