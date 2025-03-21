#pragma once
#include "Character.h"

class Ryo :	public Character
{
public:
	Ryo();
	~Ryo();

	void Init() override;
	void Render(HDC hdc) override;
	void Win(HDC hdc) override;
	void Move(int dir) override;

	void BigKick() override;
	void SmallKick() override;
	void BigPunch() override;
	void SmallPunch() override;

};

