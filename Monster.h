#pragma once

#include <iostream>

#include "Character.h"
#include "GlobalSet.h"

class Player; // Forward declaration of Player class

struct DropTable {
	// 꿈의 파편 수량
	int DreamFragments = 0;
	// 장비 
	
};

class Monster : public Character {
private:
	// Monster의 이름
	std::string Name;
	// Monster의 설명
	std::string Description;
	// Monster의 드롭 테이블
	DropTable MyDropTable;
	// Monster의 타입
	Type MonsterType;
	// Monster의 등급
	MonsterRank Rank;
	// 스킬 조건 트리거

protected:
	bool Skill_Trigger_1 = false;

public:
	// Getter
	std::string GetName() const { return Name; }
	std::string GetDescription() const { return Description; }
	Type GetMonsterType() const { return MonsterType; }
	int GetDreamFragmentsAmount() const { return MyDropTable.DreamFragments; }
	// Setter
	void SetName(const std::string& _name) { Name = _name; }
	void SetDescription(const std::string& _description) { Description = _description; }
	void SetDreamFragmentsAmount(int _amount) { MyDropTable.DreamFragments = _amount; }

public:
	virtual void Action(Player& _target) = 0;  // 몬스터의 행동을 정의하는 순수 가상 함수
	virtual void Skill_1(Player& _target) = 0; // 체력 관련 스킬을 정의하는 순수 가상 함수
	virtual void Skill_2(Player& _target) = 0; // 수면 심도 관련 스킬을 정의하는 순수 가상 함수
	virtual void Skill_3(Player& _target) = 0; // 조건부 스킬을 정의하는 순수 가상 함수
	
	virtual void TakeDamageSleepDepth(Player& _target, int _damage, bool _incOrdec); // 수면 심도 관련 피해를 처리하는 순수 가상 함수

	virtual bool CheckSkillTrigger_1() { return Skill_Trigger_1; } // 조건부 스킬 발동 여부 확인

public:
	Monster(int _maxhealth, int _atk, int _def, int _dreamFragments, MonsterRank _rank, Type _type)
		: Character(_maxhealth, _atk, _def), MyDropTable(), Rank(_rank), MonsterType(_type) {
		MyDropTable.DreamFragments = _dreamFragments;
	}
	virtual ~Monster() {}
};

