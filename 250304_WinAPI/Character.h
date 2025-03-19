#pragma once
#include "config.h"
enum class State
{
	IDLE,
	MOVE,
	DEAD,
	ATTACK,
	GUARD,
	ATTACKED
};

typedef enum AttackType
{
	NONE,
	BIG_KICK,
	SMALL_KICK,
	BIG_PUNCH,
	SMALL_PUNCH
}at;

struct Stat {
	int maxHP{ 100 };
	float moveSpeed{ 10 };
	int curHP{ 100 };
};

class Image;
class Character
{
public:
	Character();
	~Character();

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void Move(int dx, int dy);
	FPOINT GetPos() { return pos; }

	virtual void BigKick();
	virtual void SmallKick();
	virtual void BigPunch();
	virtual void SmallPunch();

	
	void SetPos(FPOINT pos) { pos = pos; }
	void SetIsFlip(bool flip) { isFlip = flip; }
	void SetFrame(int frame) { animationFrame = frame; }

	int GetAnimationFrame() { return animationFrame; }

	State GetState() { return _state; }

	inline Stat GetStat() { return stat; }
	inline void SetCurHP(int hp) { stat.curHP = hp; }

	void CheckIsAlive() { if (stat.curHP <= 0) isAlive = false; }
	bool GetIsAlive() { return isAlive; };


private:
	bool isAlive{ true };

	FPOINT pos;
	int width;
	int height;
	int speed;
	RECT attackRC;
	bool attackRCactivated{ false };
	RECT characterRC;

	at attackType{ NONE };

	Stat stat;

	Image* characterImage;
	Image* punchImage;
	Image* bigKickImage;
	int animationFrame;

	bool debugRender = true;
	bool canMove;
	bool isFlip;
	State _state;


	const float bigAttDamage{ 20 };
	const float smallAttDamage{ 10 };
	float nowAttDamage{ 0 };
};

