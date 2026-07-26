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
	Health = _health;
	if (Health > MaxHealth)
		Health = MaxHealth;
	else if (Health < 0)
		Health = 0;
}
