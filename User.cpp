#include "User.h"

User::User(MyString username, MyString password, MyString firstName, MyString lastName) : username(username) , password(password), firstName(firstName), lastName(lastName){

}
User::User() : username(""), password(""), firstName(""), lastName("") {

}

void User::setUsername(const MyString& username) {
	this->username = username;
}
void User::setPassword(const MyString& password) {
	this->password = password;
}
void User::setFirstName(const MyString& firstName) {
	this->firstName = firstName;
}
void User::setLastName(const MyString& lastName) {
	this->lastName = lastName;
}

void User::setBalance(int toSet) {
	balance = toSet;
}

const MyString& User::getUsername() const {
	return username;
}
const MyString& User::getPassword() const {
	return password;
}
const MyString& User:: getFirstName() const {
	return firstName;
}
const MyString& User::getLastName() const {
	return lastName;
}

 int User::getBalance()  {
	return balance;
}

void User::addToBalance(int toAdd) {
	if (toAdd > 0)
		balance += toAdd;
}