#include "StoreArea.h"

using namespace std;

bool StoreArea::EnterEvent(Player& _player)
{
	cout << "You have entered the Store Area." << endl;
	cout << "1 : Buy items" << endl;
	cout << "2 : Sell items" << endl;
	cout << "3 : Exit Store" << endl;
	while (true) {
		cout << "Choose an action: ";
		int action;
		cin >> action;
		switch (action)
		{
		case 1:
			cout << "Buying items..." << endl;
			// Implement buying logic here
			return true;
		case 2:
			cout << "Selling items..." << endl;
			// Implement selling logic here
			return true;
		case 3:
			cout << "Exiting Store..." << endl;
			return false;
		default:
			cout << "Invalid action. Please try again." << endl;
			break;
		}
	}
}
