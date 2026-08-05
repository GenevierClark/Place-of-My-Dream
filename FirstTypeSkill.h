#pragma once

#include "GlobalSet.h"
#include "WeaponSkill.h"

class FirstTypeSkill : public WeaponSkill {
private:
	int SkillPower; // 스킬의 공격력
	Type SkillType; // 스킬의 타입
	int CostMin, CostMax; // 스킬 사용에 필요한 최소 및 최대 비용

public:
	void Execute(Player& _player, Character& _target) override;

public:
	FirstTypeSkill(int _skillPower, Type _skillType, int _costMin, int _costMax)
		: SkillPower(_skillPower), SkillType(_skillType), CostMin(_costMin), CostMax(_costMax) {}

};

