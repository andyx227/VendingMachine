// VendingMachine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

enum VendingState {
	idle,
	verifying_amt,
	vending,
	dispense_change
};

class Item {
public :
	string name;
	float amt;

	Item(string productName, float productAmount) {
		name = productName;
		amt = productAmount;
	}
};

int main()
{
	string productChosen;
	string money;
	float change;
	VendingState state = idle;  // Vending machine initially in "idle" state
	vector<Item> items;

	Item item1 = Item("Coca Cola", 1.50);
	Item item2 = Item("Pepsi", 2.50);
	Item item3 = Item("Doritos", 3.00);
	Item item4 = Item("iPhone XS Max", 1000.75);

	items.push_back(item1);
	items.push_back(item2);
	items.push_back(item3);
	items.push_back(item4);

	cout << "Welcome to my vending machine!" << endl;
	cout << "This machine contains the following items: " << endl;
	for (int i = 0; i < items.size(); i++) {
		cout << i + 1 << ") " << items[i].name << " - $" << items[i].amt << endl;
	}

	while (productChosen != "0") {
		switch (state) {
		
		case idle:
			change = 0;  // Reset
			cout << "Please enter the number of the item you wish to purchase (enter 0 to quit): ";
			cin >> productChosen;

			if (stoi(productChosen) <= items.size()) {  // Make sure the selection is within range of items we are selling
				state = verifying_amt;
			}
			break;
		
		case verifying_amt:
			cout << "Insert your money: $";
			cin >> money;
			
			if (items[stoi(productChosen) - 1].amt > stof(money)) {  // productChosen starts from 1, so subtract 1 for array access
				cout << "You don't have enough money!" << endl;
				state = idle;
			}
			else {
				change = stof(money) - items[stoi(productChosen) - 1].amt;
				state = dispense_change;
			}
			break;
		
		case dispense_change:
			if (change > 0 && change < 1) {
				// "fixed" and "setprecision" will make sure there are 2 decimal places
				cout << "Dispensing your change of $" << fixed << setprecision(2) << change << endl;
			}

			state = vending;
			break;

		case vending:
			cout << "Good choice, vending your " << items[stoi(productChosen) - 1].name << " now!" << endl << endl << endl;
			state = idle;
		}
	}

	cout << "Thank you for visiting my vending machine! Come again..." << endl;
}
