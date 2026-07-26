#pragma once

#include "Monster.h"
#include "GlobalSet.h"

class CozySnake : public Monster {
private:
	
public:
	void Action(Player& _target) override;
	void Skill_1(Player& _target) override;
	void Skill_2(Player& _target) override;
	void Skill_3(Player& _target) override;

	bool CheckSkillTrigger_1() override;
public:
	CozySnake() : Monster(12, 2, 0, 5, MonsterRank::Normal, Type::Illusion) {
		SetName("Cozy Snake");
		SetDescription("Beneath its plush exterior, an unsettling gaze pierces through you.");
	}
};

