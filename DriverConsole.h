#pragma once
#include "ConsoleBase.h"
#include "Driver.h"

class DriverConsole : public ConsoleBase {
private:
	int indexCurrentDriver = -1;

	void logedInMenu();

public:
		DriverConsole();

		void login() override;
		
		void registerMe() override;

		void changeAddress();
		void check_messages();
	
		void acceptOrder();
		void declineOrder();
		void finishOrder();

		void acceptPayment();

};