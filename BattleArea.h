#pragma once

#include <iostream>

#include "Room.h"
#include "Monster.h"

class BattleArea : public Room {
private:
	// 해당 방에 있는 몬스터 데이터
	Monster* RoomMonster;

public:
	// Getter
	Monster* GetRoomMonster() const { return RoomMonster; }
	// Setter
	void SetRoomMonster(Monster* _monster) { RoomMonster = _monster; }

	bool EnterEvent(Player& _player) override;
	void BattleSequence(Player& _player);

public:
	BattleArea(Monster* _monster) : RoomMonster(_monster) {}
	~BattleArea() {}
};

