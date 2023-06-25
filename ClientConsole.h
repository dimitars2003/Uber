#pragma once
#include "ConsoleBase.h"
#include "Client.h"

class ClientConsole : public ConsoleBase {
private:
	int indexCurrentClient=-1;

	void logedInMenu() ;
	
	Address orderAddress();

	void assignDriver();

	bool isDriverFree();
public:
	ClientConsole();

	void login() override;
	
	void registerMe() override;

	void order();
	void checkOrder();
	void cancelOrder();

	void pay();
	void rate() ;
	void add_money();
	
};