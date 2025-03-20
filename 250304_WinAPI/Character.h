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

//enum class AnimationType
//{
//	IDLE,
//	MOVE,
//	DEAD,
//	ATTACK,
//  ATTACK2,
//  ATTACK3,
//  ATTACK4,
//	GUARD,
//	ATTACKED
//};

typedef enum AttackedType
{
	NONE,
	BIG_KICK,
	SMALL_KICK,
	BIG_PUNCH,
	SMALL_PUNCH
}at;

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
	// SetHP, SetDamage, SetState 필요

	int GetAnimationFrame() { return animationFrame; }
	int GetFrame() { return frameCount; }
	State GetState() { return _state; }
	// GetHP, GetDamage, GetCharacterRC, GetAttackRC 필요

	inline int GetHp() { return nowHp; }
	inline void SetHp(int hp) { nowHp = hp; }
	inline void isAttacked(float damage) { nowHp -= damage; }
	inline float GetDamage() { return nowAttDamage; }
	inline RECT GetCharacterRC() { return characterRC; }
	inline RECT GetAttackRC() { return attackRC; }

	void isDead();
	

private:
	FPOINT pos;
	int width;
	int height;
	int speed;
	RECT attackRC;
	bool attackRCactivated{ false };
	RECT characterRC;

	at attackType{ NONE };

	// Image 벡터화 필요함
	// vector<Image> animImages;
	// animImages[AnimationType::IDLE] <- 이런 식으로 접근해서 사용
	Image* characterImage;
	Image* punchImage;
	Image* bigKickImage;
	int animationFrame;

	int frameCount{ 0 };

	bool debugRender = true;
	bool canMove;
	bool isFlip;
	bool isLeft;
	State _state;

	const int maxHp{ 100 };
	int nowHp{ 100 };

	const float bigAttDamage{ 20 };
	const float smallAttDamage{ 10 };
	float nowAttDamage{ 0 };
};

