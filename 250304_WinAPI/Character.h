#pragma once
#include "config.h"

enum class Team
{
	NONE,
	LEFT,
	RIGHT
};

enum class State
{
	IDLE,
	MOVE,
	DEAD,
	ATTACK,
	GUARD,
	ATTACKED
};

enum ActType
{
	IDLE,
	MOVE_F,
	MOVE_B,
	DEAD,
	BIG_KICK,
	SMALL_KICK,
	BIG_PUNCH,
	SMALL_PUNCH,
	GUARD,
	ATTACKED
};

//typedef enum AttackedType
//{
//	NONE,
//	BIG_KICK,
//	SMALL_KICK,
//	BIG_PUNCH,
//	SMALL_PUNCH
//}at;

class Image;
class Character
{
public:
	Character();
	virtual ~Character();

	virtual void Init();
	void Update();
	virtual void Render(HDC hdc);
	void Release();

	virtual void Move(int dir);
	FPOINT GetPos() { return pos; }

	virtual void BigKick();
	virtual void SmallKick();
	virtual void BigPunch();
	virtual void SmallPunch();

	
	void SetPos(FPOINT pos) { pos = pos; }
	void SetIsFlip(bool flip) { isFlip = flip; }
	void SetFrame(int frame) { animationFrame = frame; }
	void SetHP(int hp);
	void SetState(State state) { this->_state = state; }
	void SetAnimationFrame(int f) { this->animationFrame = f; }
	void SetIsAttacked(bool isAttacked) { this->isAttacked = isAttacked; }
	inline void SetCanMove(bool _canMove) { this->canMove = _canMove; }
	//inline void SetAttackActivated(bool _attackRCactivated) { this->attackRCactivated = _attackRCactivated; }
	void MovedByEnemy();
	// SetHP, SetDamage, SetState 필요

	int GetAnimationFrame() { return animationFrame; }
	int GetFrame() { return frameCount; }
	State GetState() { return _state; }
	int GetCurHP() const { return hp; }
	RECT GetAttackRC() { return attackRC; }
	RECT GetCharacterRC() { return characterRC; }
	int GetDamage() { return nowAttDamage; }
	bool GetAttackActivated() { return this->attackRCactivated; }
	bool GetIsAttacked() { return this->isAttacked; }
	bool GetSpeed() { return this->speed; }
	
	// GetHP, GetDamage, GetCharacterRC, GetAttackRC 필요

protected:

	Team team{ Team::NONE };

	FPOINT pos;
	int width;
	int height;
	int speed;
	int maxHp{ 100 };
	int hp{ 100 };
	RECT attackRC;
	bool attackRCactivated{ false };
	bool isAttacked{ false };
	RECT characterRC;
	// hp, damage 필요

	//at attackType{ NONE };
	ActType actType{ IDLE };

	// Image 벡터화 필요함
	vector<Image*> animImages;
	// animImages[AnimationType::IDLE] <- 이런 식으로 접근해서 사용
	int animationFrame;
	int maxIdlePrame;

	int frameCount{ 0 };

	bool debugRender = true;
	bool canMove;
	bool isFlip;
	bool isLeft;
	State _state;
	

	const int bigAttDamage{ 20 };
	const int smallAttDamage{ 10 };
	float nowAttDamage{ 0 };
};

