#pragma once


class Character {
private:
	int MaxHealth;
	int Health;
	int AttackPower;
	int Defense;
	int TurnCount; // 턴 수를 추적하는 변수

public:
	// Getter
	int GetHealth() const { return Health; }
	int GetAttackPower() const { return AttackPower; }
	int GetDefense() const { return Defense; }
	int GetMaxHealth() const { return MaxHealth; }
	int GetTurnCount() const { return TurnCount; }
	// Setter
	virtual void SetHealth(int _health) { Health = _health; }
	void SetAttackPower(int _attackpower) { AttackPower = _attackpower; }
	void SetDefense(int _defense) { Defense = _defense; }
	void SetMaxHealth(int _maxhealth) { MaxHealth = _maxhealth; }
	void SetTurnCount(int _turncount) { TurnCount = _turncount; }

public:
	virtual void TakeDamageHealth(int _damage); // 체력 관련 피해를 처리하는 가상 함수

public:
	Character(int _maxhealth, int _atk, int _def) : MaxHealth(_maxhealth), Health(_maxhealth), AttackPower(_atk), Defense(_def), TurnCount(0) {}
	virtual ~Character() {}
};