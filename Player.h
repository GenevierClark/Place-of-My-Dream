#pragma once

#include "Character.h"
#include "GlobalSet.h"


class Player : public Character {
private:
	int MaxSleepDepth; // 최대 수면 심도
	int SleepDepth; // 수면 심도
	int DreamFragments;      // 꿈의 파편
	// 추가적인 플레이어 관련 속성들을 여기에 정의할 수 있습니다.
	ArmorEquipmentType EquippedArmor; // 방어구
	// 장신구
	AccessoryEquipmentType EquippedAccessory;
	// 인벤토리
	

public:
	// Getter
	int GetSleepDepth() const { return SleepDepth; }
	int GetDreamFragments() const { return DreamFragments; }
	int GetMaxSleepDepth() const { return MaxSleepDepth; }
	// Setter
	void SetSleepDepth(int _sleepdepth);
	void SetHealth(int _health) override;
	void SetMaxSleepDepth(int _maxsleepdepth) { MaxSleepDepth = _maxsleepdepth; }
	void SetDreamFragments(int _dreamfragments) { DreamFragments = _dreamfragments; }

	void BaseAttack(Character& _target); // 기본 공격
	// 무기에 따른 특수 스킬
	// 방어
	// 도구(소모품) 사용

public:
	Player()
		: Character(100, 1, 0), MaxSleepDepth(100), SleepDepth(100), DreamFragments(0), EquippedArmor(ArmorEquipmentType::Empty), EquippedAccessory(AccessoryEquipmentType::Empty) {}
	~Player() {}
};

