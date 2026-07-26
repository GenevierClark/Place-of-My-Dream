#include "RestArea.h"

using namespace std;

bool RestArea::EnterEvent(Player& _player)
{
	cout << "You have entered the Rest Area." << endl;
	cout << "1 : recover sleep depth" << endl;
	cout << "2 : recover health" << endl;
	cout << "3 : exit" << endl;
	int action;

	while (true) {
		cout << "Choose an action: ";
		cin >> action;
		switch (action)
		{
		case 1:
			cout << "Recovering sleep depth..." << endl;
			// Implement sleep depth recovery logic here
			RestArea::ApplySleepDepthRecovery(_player, GetSleepDepthRecoveryAmount());
			return true;
		case 2:
			cout << "Recovering health..." << endl;
			// Implement health recovery logic here
			RestArea::ApplyHealthRecovery(_player, GetHealthRecoveryAmount());
			return true;
		case 3:
			cout << "Exiting Rest Area..." << endl;
			return false;
		default:
			cout << "Invalid action. Please choose again." << endl;
			break;
		}
	}
}
