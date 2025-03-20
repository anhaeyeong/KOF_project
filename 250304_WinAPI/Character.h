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

typedef enum class Team
{
	NONE,
	LEFT,
	RIGHT
}LR;

enum ActType
{
	IDLE,
	MOVE,
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
	// SetHP, SetDamage, SetState �ʿ�

	int GetAnimationFrame() { return animationFrame; }
	int GetFrame() { return frameCount; }
	State GetState() { return _state; }
	// GetHP, GetDamage, GetCharacterRC, GetAttackRC �ʿ�

protected:
	Team team{ Team::NONE };
	FPOINT pos;
	int width;
	int height;
	int speed;
	RECT attackRC;
	bool attackRCactivated{ false };
	RECT characterRC;
	// hp, damage �ʿ�

	//at attackType{ NONE };
	ActType actType{ IDLE };

	// Image ����ȭ �ʿ���
	vector<Image*> animImages;
	// animImages[AnimationType::IDLE] <- �̷� ������ �����ؼ� ���
	int animationFrame;
	int maxIdlePrame;

	int frameCount{ 0 };

	bool debugRender = true;
	bool canMove;
	bool isFlip;
	bool isLeft;
	State _state;


	const float bigAttDamage{ 20 };
	const float smallAttDamage{ 10 };
	float nowAttDamage{ 0 };
};

