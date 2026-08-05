#include <iostream>
#include <cstdlib>

#include "Player.h"
#include "Character.h"
#include "Monster.h"
#include "FirstTypeSkill.h"



void FirstTypeSkill::Execute(Player& _player, Character& _target)
{
	// CostMin과 CostMax 사이의 랜덤 값 생성
	int RandomCost = static_cast<int>(rand()) % (CostMax - CostMin + 1) + CostMin;
	if (_player.GetSleepDepth() < RandomCost) {
		std::cout << "수면 심도가 부족하여 스킬을 사용할 수 없습니다." << std::endl;
		return; // 수면 심도가 부족하면 스킬 사용 불가
	}
	else
		_player.SetSleepDepth(_player.GetSleepDepth() - RandomCost); // 플레이어의 수면 심도 감소

	int FinalSkillPower = SkillPower; // 최종 스킬 공격력 초기화
	if (SkillType == Type::Illusion)
	{
		switch (static_cast<Monster&>(_target).GetMonsterType())
		{
		case Type::Oblivion:
			FinalSkillPower *= 2; // Oblivion 타입 몬스터에게는 스킬 공격력 2배
			break;
		case Type::Lucid:
			FinalSkillPower /= 2; // Lucid 타입 몬스터에게는 스킬 공격력 절반
			break;
		default:
			break;
		}
	}
	else if (SkillType == Type::Oblivion)
	{
		switch (static_cast<Monster&>(_target).GetMonsterType())
		{
		case Type::Lucid:
			FinalSkillPower *= 2; // Lucid 타입 몬스터에게는 스킬 공격력 2배
			break;
		case Type::Illusion:
			FinalSkillPower /= 2; // Illusion 타입 몬스터에게는 스킬 공격력 절반
			break;
		default:
			break;
		}
	}
	else if (SkillType == Type::Lucid)
	{
		switch (static_cast<Monster&>(_target).GetMonsterType())
		{
		case Type::Illusion:
			FinalSkillPower *= 2; // Illusion 타입 몬스터에게는 스킬 공격력 2배
			break;
		case Type::Oblivion:
			FinalSkillPower /= 2; // Oblivion 타입 몬스터에게는 스킬 공격력 절반
			break;
		default:
			break;
		}
	}
	if(FinalSkillPower < 1)
		FinalSkillPower = 1; // 최소 공격력은 1로 설정
	_target.TakeDamageHealth(FinalSkillPower); // 스킬 공격력만큼 체력 피해
	
}
