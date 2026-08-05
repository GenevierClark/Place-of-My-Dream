#pragma once

#include "GlobalSet.h"

class Player; // Forward declaration of Player class

class Weapon {
private:
	BaseType Base;
	SynthesisType Synthesis;

public:
	// Getter
	BaseType GetBase() const { return Base; }
	SynthesisType GetSynthesis() const { return Synthesis; }
	// Setter
	void SetBase(BaseType _base) { Base = _base; }
	void SetSynthesis(SynthesisType _synthesis) { Synthesis = _synthesis; }

public:
	void UpdatePlayerStats(Player& _player); // 플레이어의 능력치를 업데이트하는 함수


public:
	Weapon()
		: Base(BaseType::Empty), Synthesis(SynthesisType::Empty) {}
	~Weapon() {}
};

