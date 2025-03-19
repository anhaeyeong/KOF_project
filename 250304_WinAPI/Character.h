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
	
	void SetPos(FPOINT pos) { pos = pos; }
	void SetIsFlip(bool flip) { isFlip = flip; }
	void SetFrame(int frame) { animationFrame = frame; }
	//void SetHP(int hp) { hp = hp; }

	int GetAnimationFrame() { return animationFrame; }
	State GetState() { return _state; }

	/*RECT GetCharacterRC();
	RECT GetAttackRC();
	int GetDamage();
	int GetHP();
	int GetSpeed();*/

private:
	FPOINT pos;
	int width;
	int height;
	int speed;
	RECT attackRC;
	RECT characterRC;

	Image* characterImage;
	Image* punchImage;
	Image* bigKickImage;
	int animationFrame;

	bool debugRender = true;
	bool canMove;
	bool isFlip;
	State _state;
};

