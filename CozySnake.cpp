#include "CozySnake.h"
#include "Player.h"

void CozySnake::Action(Player& _target) 
{
	int TurnCount = GetTurnCount();
	switch (TurnCount % 3)
	{
	case 0:
		Skill_1(_target);
		break;
	case 1:
		Skill_2(_target);
		break;
	case 2:
		if (CheckSkillTrigger_1()) {
			Skill_3(_target);
		}
		else {
			Skill_1(_target);
		}
		break;
	default:
		break;
	}
	SetTurnCount(GetTurnCount() + 1);
}

void CozySnake::Skill_1(Player& _target) 
{
	// 꼬리를 통한 공격으로 플레이어의 체력을 감소시키는 스킬
	_target.SetHealth(_target.GetHealth() - 3); // 예시로 3만큼 체력 감소	
}

void CozySnake::Skill_2(Player & _target)
{
	// 플레이어의 수면 심도를 감소시키는 스킬
	_target.SetSleepDepth(_target.GetSleepDepth() - 5); // 예시로 5만큼 수면 심도 감소
}

void CozySnake::Skill_3(Player& _target)
{
	// 특정 조건 (예: 몬스터의 체력이 50% 이하일 때)에서만 발동되는 스킬
	SetDefense(GetDefense() + 2); // 예시로 방어력 증가
}

bool CozySnake::CheckSkillTrigger_1()
{
	// 조건 : 체력이 50% 이하일 때 발동
	if (GetHealth() <= GetMaxHealth() / 2) {
		Skill_Trigger_1 = true;
	}
	return Skill_Trigger_1;
}
