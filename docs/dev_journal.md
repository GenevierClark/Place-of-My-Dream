# 개발 학습 일지 (Dev Journal)

> 코드를 구현하면서 나눈 질문, 코드 리뷰, 설계 논의를 날짜별로 기록합니다. 나중에 복기하며 재학습하기 위한 문서라, 결론뿐 아니라 "왜 그런 결론에 도달했는지" 과정도 같이 남깁니다.
> 게임 기획(내러티브/시스템) 변경 이력은 [devlog.md](./devlog.md), 최신 기획 확정본은 [game_design.md](./game_design.md) 참고.

---

## [Day 2] 2026-07-22 — Room 클래스 계층 설계

### 1. 상속(다형성) vs enum class + switch

**질문**: 방 종류(휴식처/전투방/상점/잠긴 문)를 구분할 때, `Room`을 상속하는 서브클래스로 나눌지 아니면 `Room` 하나에 타입을 나타내는 `enum class` 필드를 두고 `switch`로 분기할지 고민.

**논의 내용**:
- **가상 함수(다형성)**: 새 방 종류를 추가할 때 새 클래스 하나만 만들면 끝. 기존 호출부 코드를 안 건드려도 됨 (Open/Closed 원칙).
- **enum class + switch**: 방 종류가 늘어날 때마다 그 타입을 다루는 모든 switch문을 찾아 case를 추가해야 함. 하나라도 빠뜨리면 조용히 버그가 됨. 대신 방 개수가 적을 땐 로직이 한 함수에 모여 있어 한눈에 보기 편함.

**결론**: `CLAUDE.md`에 "다형성을 활용한 유연한 노드 클래스 구조"가 포트폴리오 목표로 명시되어 있어서, 상속 + 가상 함수 방식으로 결정. `Room`을 추상 클래스로 만들고 `RestArea`/`BattleArea`/`StoreArea`가 상속받는 구조로 확정.

### 2. `Room::neighbors`를 `Room*`(raw pointer)로 둔 이유

`std::vector<Room*> neighbors`가 raw pointer인 이유: 인접 노드는 "소유(owning)"가 아니라 "참조(non-owning)"만 하는 관계이기 때문. 소유권은 나중에 만들 `Map`류의 컨테이너가 가지게 될 예정. `shared_ptr`을 쓸 필요가 없는 전형적인 경우.

### 3. `EnterEvent()` 함수의 반환값 설계 — 여러 번 시행착오를 거침

**1차 시도**: `virtual void EnterEvent() = 0;` — 매개변수도 반환값도 없었음.

**2차 시도**: 매개변수로 `Player*`를 받는 걸 고려. → 이 과정에서 "Player를 안 받고 방에 들어가는 상황이 있을 수 있나?"를 자문하고, 없다면 포인터보다 참조(`Player&`)가 "항상 유효한 대상이 필요하다"는 계약을 타입만으로 드러낼 수 있다는 걸 이해함. `Player&`로 확정.

**3차 시도 — 반환 타입**: "전투 로직은 따로 작성할 거니까" 반환 타입을 `bool`로 바꿈. 처음엔 "이벤트가 온전히 실행됐는가"라는 의미로 생각했으나, 리뷰 과정에서 "함수가 호출되면 내부 로직은 예외 없이 항상 끝까지 실행되는데, 그럼 언제 `false`가 되는 거지?"라는 질문에 막힘 — 이 의미는 폐기.

**4차 시도 (최종)**: "이 방에서 할 수 있는 행동이 모두 끝났는가"라는 의미로 재정의. 이건 `Room`에 이미 있던 `isVisited` 필드와 개념이 같다는 걸 발견 — `EnterEvent()`가 `true`를 반환하면 호출부가 `SetisVisited(true)`를 호출하는 식으로 연결하기로 함.

**추가로 나온 중요한 질문**: "메인 루프가 `true`를 받았을 때, 이게 전투방이었는지 상점이었는지 어떻게 알고 그에 맞는 다음 행동(전투 시작/상점 열기)을 할까?" → 답: **몰라도 된다.** 다형성을 쓰는 이유 자체가 "호출하는 쪽이 구체 타입을 몰라도 되게 만들기 위해서"이므로, "전투를 시작하는 로직"이나 "상점을 여는 로직" 자체를 메인 루프가 아니라 **`BattleArea::EnterEvent()`/`StoreArea::EnterEvent()` 내부에서 직접 처리**하도록 설계 방향을 정함. `bool`은 그저 "이 방의 상호작용이 끝나서 `isVisited`로 전환해도 되는가"만 나타내는 최소한의 신호로 남기로 함.

**최종 계약**:
```cpp
virtual bool EnterEvent(Player& _player) = 0;
// 반환값 의미: 이 방에서 할 수 있는 행동이 모두 끝났는가 (→ true면 호출부가 isVisited를 true로 설정)
// 전투/상점 등 구체적인 처리는 각 서브클래스의 override 내부에서 완결
```

### 4. `RestArea`/`BattleArea`/`StoreArea` 초기 구현 리뷰 — 발견된 버그들

**버그 1: 입력을 while 루프 밖에서 한 번만 받음 (무한루프)**
```cpp
int action;
cin >> action;        // 딱 한 번만 입력받음
while (true) {
    switch (action) {  // action 값이 안 바뀜
        case 1: ... break;  // switch만 빠져나가고 while은 계속 돎
```
`break`는 `switch`문만 빠져나가지 `while` 루프는 안 빠져나간다는 점을 놓쳐서, 1번이나 2번을 선택하면 같은 case가 무한 반복 실행됨. `cin >> action;`을 `while(true)` **안으로** 옮겨서 해결. (`RestArea`, `BattleArea`에서 발생, `StoreArea`는 처음부터 올바르게 작성됨.)

**버그 2: `StoreArea`의 "Exit" 선택지가 실제로 종료 안 됨**
```cpp
case 3:
    cout << "Exiting Store..." << endl;
    break;   // switch만 빠져나가고 while(true)은 안 끝남
```
메시지만 찍고 다시 메뉴로 돌아감. `return`을 써야 함수가 실제로 끝난다는 걸 놓친 케이스. `return false;`로 수정.

**버그 3: 루프 뒤의 도달 불가능한(dead) `return`**
```cpp
while (true) {
    ...
    case 3: return false;
}
return false;  // 여기 도달할 방법이 없음 (컴파일은 되지만 죽은 코드)
```
`while(true)`을 빠져나가는 유일한 경로가 `case`문 안의 `return`뿐이라, 루프 뒤의 `return`은 죽은 코드. 나중에 `case 1`/`2`도 각각 자기 로직이 끝나는 지점에서 바로 `return true;`하도록 구조를 정리하면서 자연스럽게 사라짐.

**버그 4: `RestArea::ApplySleepDepthRecovery`/`ApplyHealthRecovery`가 선언만 있고 구현이 없음** — `Player` 클래스가 아직 없어서 발생한 문제. `Player` 클래스를 만들기 전까지는 링커 에러(undefined reference) 상태로 보류됨.

**깨달음**: 이 과정에서 `switch`문의 `break`가 정확히 무엇을 빠져나가는지(그 `switch`문 자체만, 바깥의 반복문은 아님)에 대한 이해가 부족했다는 걸 스스로 인지함. 이후 `case`마다 로직이 끝나는 즉시 `return`으로 함수를 종료하는 패턴으로 정리하면서 문제가 해결됨.

---

## [Day 3] 2026-07-26 — Player 클래스 설계 및 RestArea 실제 구현

### 5. `std::enable_shared_from_this` 상세 설명 (이전 Text RPG 프로젝트의 `Character` 클래스 리뷰 중)

**왜 `this`를 그냥 `shared_ptr`로 감싸면 안 되는가**:
```cpp
std::shared_ptr<Character> GetSelf() {
    return std::shared_ptr<Character>(this); // 절대 하면 안 됨
}
```
이렇게 하면 원래 이 객체를 가리키던 `shared_ptr`의 컨트롤 블록과 무관한, **완전히 새로운 컨트롤 블록**이 생성됨. 참조 카운트가 0이 되는 시점이 두 번 발생해서 같은 메모리를 두 번 `delete` → 크래시.

**`enable_shared_from_this`의 동작 원리**: 이걸 상속하면 내부에 숨겨진 `weak_ptr` 멤버가 생김. `std::make_shared<T>(...)`나 `shared_ptr<T>(new T(...))`로 객체를 최초로 감쌀 때, 그 컨트롤 블록 정보가 이 내부 `weak_ptr`에 자동 연결됨. 이후 `shared_from_this()`는 내부적으로 `internal_weak_ptr.lock()`을 호출하는 것과 같아서, 컨트롤 블록이 중복 생성되지 않음.

**핵심 함정**: 생성자 내부에서는 아직 어떤 `shared_ptr`도 이 객체를 소유하지 않은 상태라, `shared_from_this()`를 호출하면 `std::bad_weak_ptr` 예외 발생. (Text RPG 프로젝트에서 `InitComponent()`를 생성자와 분리했던 이유가 바로 이것.) 마찬가지로, `shared_ptr`로 감싸지 않은 객체(스택 객체, 그냥 `new`로 만든 객체)에 대고 호출해도 동일하게 터짐.

**Place of My Dream 적용 여부**: 지금 `Room`이 `Player&`를 참조로만 받는 구조라 당장은 `enable_shared_from_this`가 필요 없음. `Player`의 소유권을 어떻게 관리할지(예: 중앙 매니저가 `shared_ptr`로 소유)는 아직 미정.

### 6. 게임 전체 구조 — 중앙 매니저 vs 탈중앙화

**질문**: 지금 만드는 게임 구조에서 이전 프로젝트의 `GameManager`처럼 중앙에서 관리하는 클래스를 둘지, 아니면 각자 관리하게 할지.

**논의 내용**:
- **중앙 매니저(Owner) 패턴**: 하나의 클래스가 플레이어/맵/진행 상태를 다 들고 메인 루프를 굴림. 상용 게임에도 `GameMode`, `GameInstance` 등으로 거의 항상 존재. 특히 로그라이크는 "현재 Run의 상태"를 한 곳에서 관리하는 게 자연스러워 흔한 패턴.
- **탈중앙화**: `MapManager`, `CombatManager`처럼 도메인별로 나눠 느슨하게 협력. 결합도는 낮아지지만 설계 난이도가 올라감. 팀/대규모 프로젝트에 적합, 30일 솔로 프로젝트엔 오버엔지니어링 가능성.

**결론**: 중앙 매니저 방식으로 진행하기로 함. 단, 이전 프로젝트에서 `GameManager`/`ItemDataManager`/`EnemyDataManager`를 전부 Singleton으로 만들었던 것에 대한 리뷰 피드백(전역 상태가 퍼지면 추적이 어려워짐)을 참고해서, 이번엔 Singleton이 아니라 `main()`에서 지역 변수로 소유하는 형태를 고려 중 (아직 확정은 아님, 실제 구현 시 다시 판단 예정).

### 7. 캐릭터 스탯의 자료형 선택

**질문**: HP/ATK/DEF 같은 스탯을 지금까지 `int`로만 써왔는데, 게임 구조에서 보통 어떤 자료형을 쓰는지.

**논의 내용**:
- `int`가 실제로 가장 흔함 — 지금까지의 방식이 틀린 게 아님.
- 고정 폭 정수 타입(`int32_t`, `int16_t` 등, `<cstdint>`)은 크기가 플랫폼에 상관없이 고정됨. `game_design.md`에 적힌 "구조체 메모리 패딩/정렬 최적화", 이진 직렬화(세이브 파일) 목표와 직결되는 선택지 — 나중에 세이브/직렬화를 본격적으로 다룰 때 고려하기로 함.
- `float`/`double`은 크리티컬 확률, 데미지 배율처럼 소수점이 필요한 값에만 쓰고, HP처럼 플레이어가 직접 보는 핵심 스탯은 정수로 유지하는 게 일반적 (부동소수점 비교/반올림 문제 회피).
- `unsigned int`의 함정: HP가 논리적으로 음수가 안 된다고 해서 `unsigned`로 하면 위험함 — `Health - Damage`에서 `Damage`가 `Health`보다 크면 음수로 안 내려가고 매우 큰 양수로 wrap-around됨. 그래서 계산 중간에 음수를 거칠 수 있는 값은 부호 있는 `int`로 두고, 0 이하가 되면 별도로 클램프하는 방식이 일반적.

**결론**: 지금은 `int`로 계속 진행, 세이브/직렬화 단계에서 고정 폭 타입 전환을 고려.

### 8. 참조를 지역 "별명"으로 쓰는 기법

**질문**: 변수명은 명확성을 위해 길게 짓고 싶은데, 매번 긴 이름을 쓰기 번거로우니 별명을 붙이는 기법이 있는지.

**답변 요지**:
```cpp
void SomeFunction() {
    int& hp = Health;  // Health의 지역 별명
    hp = 100;          // Health = 100;과 동일한 효과
}
```
`int& hp = Health;`는 새 변수를 만드는 게 아니라 `Health`를 가리키는 또 다른 이름을 만드는 것. 그 함수/스코프 안에서만 유효한 지역적 별명이라, 멤버 변수의 "공식 이름"(`Health`)은 명확하게 유지하면서 반복 사용은 짧게 할 수 있음.

**아닌 것들**: `using` 타입 별명(`using HP = int;`)은 **타입**에 붙는 것이지 **변수**에 붙는 게 아니라서 이 문제를 해결 못함. `#define` 매크로도 기술적으론 가능하지만 스코프 개념이 없어 부작용이 많아 현대 C++에선 지양.

### 9. `Character`/`Player` 클래스 구현 리뷰 — 초기화 누락 버그

**1차 작성본의 문제**:
```cpp
class Character {
private:
    int MaxHealth;   // 생성자가 없어서 초기화가 안 됨
    int Health;
    int AttackPower;
    int Defense;
public:
    int GetMaxHealth() const { return MaxHealth; }
    // SetMaxHealth()가 아예 없음 — 값을 넣을 방법 자체가 없었음
    ...
};
```
`Player()` 생성자에서 `SetHealth(100), SetAttackPower(1), SetDefense(0);`으로 세팅했지만, `MaxHealth`와 (`Player`의) `MaxSleepDepth`는 어디에도 초기화되는 곳이 없어서 **쓰레기 값**으로 남아있었음. `MaxHealth`는 setter조차 없었고, `MaxSleepDepth`는 getter/setter가 아예 둘 다 없었음. `game_design.md`상 "단련: Max HP 증가", "층 클리어마다 수면 심도 최대치 확장" 같은 핵심 기능에 쓰일 값들이라 실질적인 버그로 판단.

**추가로 발견된 것 — 콤마 연산자 오용**:
```cpp
SetHealth(100), SetAttackPower(1), SetDefense(0);
```
세미콜론 세 개로 나눈 것처럼 보이지만 실제로는 **콤마 연산자**로 묶인 하나의 문장. 세 함수가 순서대로 호출되긴 해서 결과적으로는 작동했지만, 콤마 연산자는 다른 문맥에서 예상치 못한 동작을 유발할 수 있는 함정 — 의도한 게 아니라면 세미콜론으로 나누는 게 맞다는 피드백.

**설계 선택지 논의 — 생성자로 초기화 vs setter 호출**: `Character`의 멤버가 전부 `private`이라 `Player`가 초기화 리스트에 직접 못 넣는 상황. 대안으로 `Character(int _health, int _atk, int _def)`처럼 매개변수 생성자를 만들고 `Player() : Character(100, 1, 0), ... {}`처럼 위임하는 방식을 제시. "생성자 위임 방식은 필수 스탯 없이는 객체를 만들 수 없다는 걸 타입 시스템 차원에서 강제해서, 지금 겪은 것 같은 초기화 누락 실수를 원천적으로 방지한다"는 게 핵심 장점.

**최종 수정본**:
```cpp
// Character.h
Character(int _maxhealth, int _atk, int _def)
    : MaxHealth(_maxhealth), Health(_maxhealth), AttackPower(_atk), Defense(_def) {}

// Player.h
Player()
    : Character(100, 1, 0), MaxSleepDepth(100), SleepDepth(100), Money(0) {}
```
생성자 위임 방식으로 변경, `SetMaxHealth()`/`MaxSleepDepth` getter·setter 추가. `Health(_maxhealth)`로 시작 체력을 최대 체력과 같게 설정한 것도 자연스러운 설계로 확인됨.

### 10. 포인터 vs 참조 — 실제 매개변수 설계에 적용

**질문**: `Room::EnterEvent`류 함수에서 `Player&`(참조)로 원본을 받아왔는데, 포인터로 주소를 받는 것과의 차이가 궁금함.

**핵심 차이 3가지**:
1. **null이 될 수 있는가**: 포인터는 `nullptr` 가능(대상이 없을 수 있음을 타입으로 표현). 참조는 한번 초기화되면 반드시 유효한 객체를 가리켜야 함 — "이 함수엔 항상 유효한 대상이 들어온다"는 계약을 표현할 때 적합.
2. **재바인딩(다른 대상으로 바꿔치기) 가능한가**: 포인터는 나중에 다른 객체를 가리키도록 재할당 가능. 참조는 한번 묶이면 스코프가 끝날 때까지 절대 다른 객체로 안 바뀜 (`ref = other;`는 재바인딩이 아니라 값 복사 대입임에 주의).
3. **호출부 코드의 명확성**: `Foo(&player)`는 `&`로 "이 함수가 원본을 바꿀 수도 있다"는 걸 눈에 띄게 알려줌. `Bar(player)`는 겉보기엔 값 전달처럼 보여서, 참조 매개변수는 안 바꿀 거면 `const`를 붙이는 관례가 있음.

**Place of My Dream에서의 판단**: "Player는 하나뿐이고 게임 진행 중엔 항상 존재하니, 방에 들어갔을 때 실행되는 함수들엔 반드시 유효한 Player가 있어야 한다"는 논리로 참조가 맞다고 스스로 결론 — 핵심 판단 기준은 **"이 함수가 호출되는 시점에 대상이 없을 수 있는가?"**임을 확인.

### 11. `const Player&`가 맞는지에 대한 오해 정정

**질문/오해**: "Player는 하나뿐이고 안 바뀌니까, `const Player&`로 선언하는 게 맞지 않을까?"

**정정 내용**: `const`는 "유일한 존재인가/안 바뀌는 대상을 가리키는가"가 아니라 **"이 함수가 참조를 통해 객체를 수정할 것인가"**를 나타내는 것. `RestArea::EnterEvent`나 `ApplySleepDepthRecovery` 같은 함수들은 결국 `_player.SetHealth(...)`처럼 상태를 직접 바꾸는 게 목적이므로, `const Player&`로 선언하면 `const`가 아닌 멤버 함수(`SetHealth` 등) 호출 시 컴파일 에러가 남.

**정리된 기준**:
- 읽기만 하는 함수(예: 상태 출력) → `const Player&`
- 상태를 바꾸는 함수(회복 로직 등) → `const` 없이 `Player&`

"참조 vs 포인터"와 "const 여부"는 서로 다른 기준(전자는 유효성/재바인딩, 후자는 수정 가능 여부)이라는 걸 명확히 구분해서 이해함.

### 12. `RestArea` 실제 구현 리뷰

**잘된 점**:
- `if(!GetisVisited())`로 재방문 시 다른 메뉴(퇴장만 가능)를 보여주는 처리 — "1회성 사용 후 빈 방" 설계를 정확히 구현.
- 이미 가득 찬 경우("Your sleep depth is already full") 안내 후 재선택 가능하게 만든 UX 처리.
- `case 4`(그냥 나가기)는 `isVisited`를 바꾸지 않아서, 나중에 다시 들어와 사용할 수 있도록 의도에 맞게 구현됨.

**지적된 문제**:
1. **`std::min` 사용 시 `<algorithm>` include 누락** — `Character.h`/`Room.h`/`Player.h`/`<iostream>` 어디에도 `<algorithm>`이 없는데 `std::min`을 씀. `InventoryComponent.h`의 `<memory>` 누락과 같은 패턴(우연히 컴파일되지만 이식성 없는 상태). → 수정 완료.
2. **`RestArea::ApplySleepDepthRecovery(...)`처럼 자기 클래스 멤버 함수를 클래스명으로 한정해서 호출** — 같은 클래스 안에서 호출하는 거라 불필요. `ApplySleepDepthRecovery(...)`만으로 충분. → 수정 완료.
3. **`game_design.md`와 실제 구현의 불일치 발견**: 문서엔 휴식처가 `[휴식: HP 30% 회복]` 또는 `[단련: Max HP +5]` 두 가지뿐인데, 실제 구현은 수면 심도 회복 / 체력 회복(정액) / 최대 체력 증가 세 가지. 확인 결과 세 선택지는 원래 기획된 내용이었고 문서에 옮기는 과정에서 누락된 것으로 확인. 체력 회복 방식(정액 vs 비율)은 아직 미결정. 구체적인 수치는 밸런스 조정 대상이라 문서에서 확정 수치 표기를 제거하고 미정으로 남기기로 함 → `game_design.md`/`devlog.md`에 반영.

---

## 지금까지의 핵심 교훈 정리

- **`switch`의 `break`는 `switch`문만 빠져나간다.** 바깥의 반복문(`while` 등)은 안 빠져나가므로, 반복문까지 종료하려면 `return`/`break`(라벨) 등을 명시적으로 써야 함.
- **다형성의 핵심은 "호출부가 구체 타입을 몰라도 되게 만드는 것"** — 타입별로 다른 처리가 필요하면, 호출부에서 타입을 판별하려 하지 말고 그 처리를 가상 함수 내부로 밀어 넣을 방법을 먼저 고민할 것.
- **참조 vs 포인터는 "대상이 없을 수 있는가/재바인딩이 필요한가"로 판단**, **const 여부는 "이 함수가 대상을 수정하는가"로 판단** — 서로 다른 축의 결정.
- **멤버 변수가 많아지면 생성자 없이 기본 생성 후 setter로 채우는 방식은 초기화 누락 실수를 유발하기 쉽다** — 필수 값은 매개변수 생성자로 강제하는 게 안전함.
- **쓰는 헤더는 항상 직접 include할 것** — 다른 헤더의 전이(transitive) include에 기대면 컴파일러/플랫폼이 바뀔 때 깨질 수 있음 (`<memory>`, `<algorithm>` 두 번 반복된 실수).
- **기획 문서(`game_design.md`)와 실제 코드가 어긋나면 그때그때 확인하고 문서를 갱신할 것** — 구현하다 보면 기획 당시 생각하지 못한 디테일이 나오는 게 자연스러우니, 발견 즉시 문서에 반영하는 습관이 중요.
