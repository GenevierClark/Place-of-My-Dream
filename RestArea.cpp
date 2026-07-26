#include <algorithm>

#include "RestArea.h"

using namespace std;

void RestArea::ApplySleepDepthRecovery(Player& _player, int _amount)
{
	_player.SetSleepDepth(min(_player.GetSleepDepth() + _amount, _player.GetMaxSleepDepth()));
}

void RestArea::ApplyHealthRecovery(Player & _player, int _amount)
{
	_player.SetHealth(min(_player.GetHealth() + _amount, _player.GetMaxHealth()));
}

void RestArea::IncreaseMaxHealth(Player& _player, int _amount)
{
	_player.SetMaxHealth(_player.GetMaxHealth() + _amount);
}

bool RestArea::EnterEvent(Player& _player)
{
	if(!GetisVisited()) {
		cout << "You have entered the Rest Area." << endl;
		cout << "1 : recover sleep depth (+" << GetSleepDepthRecoveryAmount() << ")" << endl;
		cout << "2 : recover health (+" << GetHealthRecoveryAmount() << ")	" << endl;
		cout << "3 : increase health through exercise (max health + " << GetMaxHealthIncreaseAmount() << ")" << endl;
		cout << "4 : exit" << endl;
		int action;

		while (true) {
			cout << "Choose an action: ";
			cin >> action;
			switch (action) {
			case 1:
				if (_player.GetSleepDepth() >= _player.GetMaxSleepDepth()) {
					cout << "Your sleep depth is already full." << endl;
					break;
				}
				else {
					cout << "Recovering sleep depth..." << endl;
					// Implement sleep depth recovery logic here
					ApplySleepDepthRecovery(_player, GetSleepDepthRecoveryAmount());
					SetisVisited(true);
					return true;
				}
			case 2:
				if (_player.GetHealth() >= _player.GetMaxHealth()) {
					cout << "Your health is already full." << endl;
					break;
				}
				else {
					cout << "Recovering health..." << endl;
					// Implement health recovery logic here
					ApplyHealthRecovery(_player, GetHealthRecoveryAmount());
					SetisVisited(true);
					return true;
				}
			case 3:
				cout << "Increasing max health..." << endl;
				// Implement max health increase logic here
				IncreaseMaxHealth(_player, GetMaxHealthIncreaseAmount());
				SetisVisited(true);
				return true;
			case 4:
				cout << "Exiting Rest Area..." << endl;
				return false;
			default:
				cout << "Invalid action. Please choose again." << endl;
				break;
			}
		}
	}
	else {
		cout << "You have already visited this Rest Area." << endl;
		cout << "1 : Exit" << endl;
		int action;
		while (true) {
			cout << "Choose an action: ";
			cin >> action;
			switch (action) {
			case 1:
				cout << "Exiting Rest Area..." << endl;
				return false;
			default:
				cout << "Invalid action. Please choose again." << endl;
				break;
			}
		}
	}
}
