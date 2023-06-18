#pragma once
#include "MyString.h"

class User {
private:
	MyString username;
	MyString password;
	MyString firstName;
	MyString lastName;
	int balance = 0;

public:
	User(MyString username, MyString password, MyString firstName, MyString lastName);
	User();
	
	void setUsername(const MyString& username);
	void setPassword(const MyString& password);
	void setFirstName(const MyString& firstName);
	void setLastName(const MyString& lastName);
	void setBalance(int toSet);

	const MyString& getUsername() const;
	const MyString& getPassword() const;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	const int getBalance() ;

	virtual ~User() = default;
	
	
	void addToBalance(int toAdd);

};