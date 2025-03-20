#pragma once

#include "Character.h"
class Image;

class Clark : public Character
{
private:

public:

	void Init();
	void Render(HDC hdc);

	void BigKick();
	void SmallKick();
	void BigPunch();
	void SmallPunch();

};

