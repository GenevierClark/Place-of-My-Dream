#include "BattleArea.h"
#include "Player.h"

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
			GetRoomMonster()->SetTurnCount(0); // Reset monster's turn count at the start of battle
			BattleSequence(_player);
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

void BattleArea::BattleSequence(Player& _player) {
	while (true) {
		// Phase 1 - 상태이상/buff/debuff 처리

		// Phase 2 - 행동 결정 및 실행
		bool IsTurnOver = false;
		while (!IsTurnOver) {
			// Player's turn
			cout << "Player's turn. Choose an action: " << endl;
			cout << "1 : Attack" << endl;
			cout << "2 : Use Item" << endl;
			cout << "3 : Check Enemy Info" << endl;
			int PlayerAction;
			cin >> PlayerAction;
			switch (PlayerAction)
			{
			case 1:
				cout << "Player attacks the monster!" << endl;
				// Implement attack logic here
				IsTurnOver = true;
				break;
			case 2:
				// Implement item usage logic here
				IsTurnOver = true;
				break;
			case 3:
				cout << "Monster Info: " << endl;
				cout << "Name: " << GetRoomMonster()->GetName() << endl;
				cout << "Description: " << GetRoomMonster()->GetDescription() << endl;
				cout << "Health: " << GetRoomMonster()->GetHealth() << "/" << GetRoomMonster()->GetMaxHealth() << endl;
				cout << "Attack Power: " << GetRoomMonster()->GetAttackPower() << endl;
				cout << "Defense: " << GetRoomMonster()->GetDefense() << endl;
				break;
			default:
				cout << "Invalid action. Please choose again." << endl;
				break;
			}
		}
		// 몬스터 생존 여부 확인
		if (GetRoomMonster()->GetHealth() <= 0) {
			cout << "Monster defeated!" << endl;
			_player.SetDreamFragments(_player.GetDreamFragments() + GetRoomMonster()->GetDreamFragmentsAmount());
			return;
		}
		// Monster's turn
		cout << "Monster's turn." << endl;
		GetRoomMonster()->Action(_player);

		// 플레이어 생존 여부 확인
		if (_player.GetHealth() <= 0) {
			cout << "Player has been defeated!" << endl;
			return;
		}
	}
}
