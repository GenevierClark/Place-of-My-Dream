#pragma once

class Character {
protected:
	int MaxHealth;
	int Health;
	int AttackPower;
	int Defense;

public:
	// Getter
	int GetHealth() const { return Health; }
	int GetAttackPower() const { return AttackPower; }
	int GetDefense() const { return Defense; }
	int GetMaxHealth() const { return MaxHealth; }
	// Setter
	virtual void SetHealth(int _health) { Health = _health; }
	void SetAttackPower(int _attackpower) { AttackPower = _attackpower; }
	void SetDefense(int _defense) { Defense = _defense; }
	void SetMaxHealth(int _maxhealth) { MaxHealth = _maxhealth; }
public:
	Character(int _maxhealth, int _atk, int _def) : MaxHealth(_maxhealth), Health(_maxhealth), AttackPower(_atk), Defense(_def) {}
	virtual ~Character() {}
};