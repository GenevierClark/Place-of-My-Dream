#pragma once

#include "Character.h"

class Player : public Character {
private:
	int MaxSleepDepth; // 최대 수면 심도
	int SleepDepth; // 수면 심도
	int DreamFragments;      // 꿈의 파편

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

public:
	Player()
		: Character(100, 1, 0), MaxSleepDepth(100), SleepDepth(100), DreamFragments(0) {
	}
	~Player() {}
};

