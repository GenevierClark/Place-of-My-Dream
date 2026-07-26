#include "BattleArea.h"

using namespace std;

bool BattleArea::EnterEvent(Player& _player)
{
	cout << "You have entered the Battle Area." << endl;
	cout << "1 : Prepare for battle" << endl;
	cout << "2 : Fight the monster" << endl;
	cout << "3 : Flee from battle" << endl;
	int action;


	while (true) {
		cout << "Choose an action: ";
		cin >> action;
		switch (action)
		{
		case 1:
			cout << "Preparing for battle..." << endl;
			// Implement preparation logic here
			return true;
		case 2:
			cout << "Fighting the monster..." << endl;
			// Implement battle logic here
			return true;
		case 3:
			cout << "Fleeing from battle..." << endl;
			// Implement fleeing logic here
			return false; // Assuming fleeing ends the event
		default:
			cout << "Invalid action. Please choose again." << endl;
			break;
		}
	}
}
