#include "Monster.h"
#include "Player.h"

void Monster::TakeDamageSleepDepth(Player& _target, int _damage, bool _incOrdec)
{
	if (_incOrdec) {
		_target.SetSleepDepth(_target.GetSleepDepth() + _damage);
	}
	else {
		_target.SetSleepDepth(_target.GetSleepDepth() - _damage);
	}
}
