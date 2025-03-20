#pragma once

#include "Character.h"
class Image;

class Clark : public Character
{
private:
	//��ǥ ������
	const int idleModifiedX{ 10 };
	int idleModifiedY;

	int smallPunchModifiedX{ 49 };
	int smallPunchModifiedY;

	int bigPunchModifiedX{ 35 };
	int bigPunchModifiedY;

	int smallKickModifiedX{ 70 };
	int smallKickModifiedY;

	int bigKickModifiedX{ 5 };
	int bigKickModifiedY;

	//�ʺ�, ���� ������
	int moveModifiedWidth;
	int moveModifiedHeight;

	int moveBModifiedWidth;
	int moveBModifiedHeight;

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

