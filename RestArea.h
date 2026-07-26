#pragma once

#include <iostream>

#include "Room.h"
#include "Player.h"

class RestArea : public Room {
private:
	// 수면 심도 회복량
	int SleepDepthRecoveryAmount;
	// 체력 회복량
	int HealthRecoveryAmount;
	// 최대 체력 증가량
	int MaxHealthIncreaseAmount;
	// 현재 Round(감정의 층)

public:
	// Getter
	int GetSleepDepthRecoveryAmount() const { return SleepDepthRecoveryAmount; }
	int GetHealthRecoveryAmount() const { return HealthRecoveryAmount; }
	int GetMaxHealthIncreaseAmount() const { return MaxHealthIncreaseAmount; }

	// Setter
	void SetSleepDepthRecoveryAmount(int _amount) { SleepDepthRecoveryAmount = _amount; }
	void SetHealthRecoveryAmount(int _amount) { HealthRecoveryAmount = _amount; }
	void SetMaxHealthIncreaseAmount(int _amount) { MaxHealthIncreaseAmount = _amount; }
	
	// 행동 선택 시 회복량 적용
	void ApplySleepDepthRecovery(Player& _player, int _amount);
	void ApplyHealthRecovery(Player& _player, int _amount);
	void IncreaseMaxHealth(Player& _player, int _amount);

	bool EnterEvent(Player& _player) override;
public:
	RestArea() : SleepDepthRecoveryAmount(10), HealthRecoveryAmount(20), MaxHealthIncreaseAmount(10) {}
	~RestArea() {}
};

