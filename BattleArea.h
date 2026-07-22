#pragma once

#include <iostream>

#include "Room.h"

class BattleArea : public Room {
private:
	// 해당 방에 있는 몬스터 데이터

	// 현재 Round

	// Reward Item

	// Reward Gold
	int RewardGold;

public:
	// Getter
	int GetRewardGold() const { return RewardGold; }

	bool EnterEvent(Player& _player) override;
public:
	BattleArea() : RewardGold(100) {}
	~BattleArea() {}
};

