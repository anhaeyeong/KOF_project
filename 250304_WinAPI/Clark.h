#pragma once

#include "Character.h"
class Image;

class Clark : public Character
{
private:
	int moveModifiedWidth;
	int moveModifiedHeight;

	int smallPunchModifiedWidth;
	int smallPunchModifiedHeight;

	int bigPunchModifiedWidth;
	int bigPunchModifiedHeight;

	int smallKickModifiedWidth;
	int smallKickModifiedHeight;

	int bigKickModifiedWidth;
	int bigKickModifiedHeight;

public:

	void Init() override;
	void Render(HDC hdc)override;

	void Move(int dir)override;

	void BigKick()override;
	void SmallKick()override;
	void BigPunch()override;
	void SmallPunch()override;

};

