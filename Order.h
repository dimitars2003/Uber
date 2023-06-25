#pragma once
#include "Address.h"

class Order {
private:
	Address currentAddress;
	Address destination;
	int cost = 0;
	int minutesLeft = 0;
	int idClient = -1;
	int idDriver = -1;
	int isAccepted = 0;
	int rating = 0;

	
	bool isFinished = 0;
	bool isPaid = 0;
	bool isPaymentRecieved = 0;

public:
	Order() = default;
	Order(Address current, Address destination, int idClient);

	void setCurrentAddress(const Address& current);
	void setDestination(const Address& destination);
	void setCost(int cost);
	void setIdClient(int idClient);
	void setIdDriver(int idDriver);
	void setIsAccepted(int isAccepted);
	void setIsFinished(bool isFinished);
	void setIsPaid(bool isPaid);
	void setRated(int isRated);
	void setPaymentRecieved(bool isPaymentRecieved);
	void setMinutesLeft(int minutesLeft);

	const Address& getCurrentAddress() const;
	const Address& getDestination() const;
	const int getCost() const;
	const int getIdClient() const;
	const int getIdDriver() const;
	const int getIsAccepted() const;
	const bool getIsFinished() const;
	const bool getIsPaid() const;
	const int getRated() const;
	const bool getPaymentRecieved() const;
	const int getMinutesLeft() const;


	bool isOrderCompleted() const;
	bool isOrderDeclined() const;
	bool isOrderAccepted() const;
	bool isRated() const;
};

