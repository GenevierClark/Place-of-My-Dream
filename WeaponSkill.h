#pragma once

class Character; // Forward declaration of Character class
class Player; // Forward declaration of Player class

class WeaponSkill {
public:
	virtual void Execute(Player& _player, Character& _target) = 0; // 스킬 실행을 정의하는 순수 가상 함수
};



