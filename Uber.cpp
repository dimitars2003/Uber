// Uber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "MyString.h"
#include <string>
#include "ClientConsole.h"

int log() {

    std::cout << "\nIf you wish you can login or register \n";
    std::cout << "1. Login\n";
    std::cout << "2. Register\n";
    std::cout << "To return to main menu enter 0\n";
    int choice = 0;
    std::cin >> choice;
    return choice;
}

void clientLog() {
    ClientConsole clientManager;
    while (true) {
        int choice = log();
        
        if (choice == 1) {
            clientManager.login();
            std::cout << "1. login\n";
        }
        else if (choice == 2) {
            clientManager.registerMe();
            std::cout << "2. register\n";
        }
        else {
            return;
        }
    }
}

void driverLog() {
    while (true) {
        int choice = log();
        if (choice == 1) {
            std::cout << "1. login\n";
        }
        else if (choice == 2) {
            std::cout << "2. login\n";
        }
        else {
            return;
        }
    }
}

int mainMenu() {

    std::cout << "Hello, are you a client or a driver \n";
    std::cout << "1. Client\n";
    std::cout << "2. Driver\n";
    std::cout << "To exit the app enter 0\n";
    int choice = 0;
    std::cin >> choice;
    
    if (choice == 1) {
        clientLog();
    }
    else if (choice == 2) {
        driverLog();
    }
    else {
        return 1;
    }
}

int main()
{
    while (true) {
        
        if (mainMenu()==1) {
            break;
        }
        
    }
     
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
