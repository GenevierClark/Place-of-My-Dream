#include "Character.h"

void Character::TakeDamageHealth(int _damage)
{
	this->SetHealth(this->GetHealth() - _damage);
}
