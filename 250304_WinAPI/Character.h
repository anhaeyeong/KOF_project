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
	// SetHP, SetDamage, SetState �ʿ�

	int GetAnimationFrame() { return animationFrame; }
	int GetFrame() { return frameCount; }
	State GetState() { return _state; }
	int GetCurHP() const { return hp; }
	// GetHP, GetDamage, GetCharacterRC, GetAttackRC �ʿ�

private:
	FPOINT pos;
	int width;
	int height;
	int speed;
	int maxHp;
	int hp;
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

