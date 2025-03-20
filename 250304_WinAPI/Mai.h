#pragma once
#include "Character.h"
class Mai : public Character
{
public:
	Mai();
	~Mai();

	void Init() override;
	void Render(HDC hdc) override;
	void Move(int dir) override;

	void BigKick() override;
	void SmallKick() override;
	void BigPunch() override;
	void SmallPunch() override;

};

