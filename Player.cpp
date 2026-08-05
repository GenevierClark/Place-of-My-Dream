#include "Character.h"
#include "Player.h"

void Player::SetSleepDepth(int _sleepdepth)
{
	SleepDepth = _sleepdepth;
	if (SleepDepth > MaxSleepDepth)
		SleepDepth = MaxSleepDepth;
	else if (SleepDepth < 0)
		SleepDepth = 0;
}

void Player::SetHealth(int _health)
{
	Character::SetHealth(_health);
	if (GetHealth() > GetMaxHealth())
		Character::SetHealth(GetMaxHealth());
	else if (GetHealth() < 0)
		Character::SetHealth(0);
}

void Player::BaseAttack(Character& _target)
{
	
}
