#pragma once

#include <iostream>

#include "Room.h"

class StoreArea : public Room {
private:
	// StoreArea에서 판매하는 아이템 데이터
	// 현재 Round

public:
	bool EnterEvent(Player& _player) override;
};

