#pragma once

#include <iostream>
#include <vector>

class Player; // Forward declaration of Player class

class Room {
private:
	std::vector<Room*> neighbors;
	bool isVisited;

public:
	// Getter
	bool GetisVisited() const { return isVisited; }

	// Setter
	void SetisVisited(bool visited) { isVisited = visited; }

	// 인접 Room 주소 반환

	// 인접 Room 추가

	// 입장 시 발생 이벤트
	virtual bool EnterEvent(Player& _player) = 0;
	// 반환 값의 의미 : 이 방에서 할 수 있는 행동이 모두 끝났는가 (-> true라면 호출부가 isVisited를 true로 설정)
public:
	Room() : isVisited(false) {}
	virtual ~Room() {}
};
