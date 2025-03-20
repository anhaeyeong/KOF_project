#include "Ryo.h"
#include "Image.h"
#include "CommonFunction.h"

Ryo::Ryo()
{
}

Ryo::~Ryo()
{
}

void Ryo::Init()
{
	pos.x = WINSIZE_X - 700;
	pos.y = WINSIZE_Y - 150;
	width = 100;
	height = 200;
	characterRC = GetRectAtCenter(pos.x - 20, pos.y, width - 50, height - 50);
	animationFrame = 0;
	speed = 10;
	isFlip = false;
	isLeft = true;
	_state = State::MOVE;
	canMove = true;

	//animImages.resize(9);
	animImages.push_back(nullptr);
	Image* characterImage = new Image();
	if (FAILED(characterImage->Init(TEXT("Image/Ryo_Smove_Front.bmp"), 1097, 300, 6, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Ryo_Smove_Front.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}
	animImages.push_back(characterImage);
	animImages.push_back(nullptr);
	Image* bigKickImage = new Image();
	if (FAILED(bigKickImage->Init(TEXT("Image/Ryo_high_kick.bmp"), 3843, 370, 10, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Ryo_high_kick.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}
	animImages.push_back(bigKickImage);
	Image* smallKickImage = new Image();
	if (FAILED(smallKickImage->Init(TEXT("Image/Ryo_middle_kick.bmp"), 2485, 360, 6, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Ryo_middle_kick.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}
	animImages.push_back(smallKickImage);
	animImages.push_back(nullptr);
	Image* smallPunchImage = new Image();
	if (FAILED(smallPunchImage->Init(TEXT("Image/Ryo_small_punch.bmp"), 906, 300, 3, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Ryo_small_punch.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}
	animImages.push_back(smallPunchImage);

	// animImages.resize(�ִϸ��̼� ����);
	// if(FAILED(animImages[AnimationType::IDLE].Init(~~~));

	attackRC = GetRectAtCenter(-10, -10, 10, 20); //��Ʈ ����
}

void Ryo::Render(HDC hdc)
{
	//if (!characterImage)	return;

	if (_state == State::MOVE)
		animImages[ActType::MOVE]->Render(hdc, pos.x, pos.y, animationFrame, width, height, isFlip);

	if (_state == State::ATTACK)

	{
		switch (actType)
		{
		case BIG_KICK:
			animImages[ActType::BIG_KICK]->Render(hdc, pos.x + 40, pos.y - 18, animationFrame, width + 100, height + 25, isFlip);
			//bigKickImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		case SMALL_KICK:
			animImages[ActType::SMALL_KICK]->Render(hdc, pos.x + 30, pos.y - 20, animationFrame, width + 120, height + 35, isFlip);
			//bigKickImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		case SMALL_PUNCH:
			animImages[ActType::SMALL_PUNCH]->Render(hdc, pos.x, pos.y, animationFrame, width + 50, height, isFlip);
			//smallPunchImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		}
	}

	// state�� ���� �̹��� ������
	// if(_state == ~~~) 
	//  animImages[AnimationType::~~~]->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
	// -> AnimationType�� �ʿ��������? �׳� animImages[State::~~]->Render() �����غ���

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	if (debugRender)
		RenderRectAtCenter(hdc, pos.x - 20, pos.y, characterRC.right - characterRC.left, characterRC.bottom - characterRC.top);
	if (attackRCactivated == true)
		RenderRect(hdc, attackRC.left, attackRC.top, attackRC.right - attackRC.left, attackRC.top - attackRC.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
}

void Ryo::Move(int dir)
{
	if (canMove == false) return;
	if (animationFrame >= 5)	animationFrame = 0;
	pos.x += dir * speed;
	//pos.y += dy;
	animationFrame++;
}

void Ryo::BigKick()
{
	if (animationFrame >= 3 && animationFrame <= 5) {
		attackRCactivated = true;
		nowAttDamage = bigAttDamage;

		SetRectAtCenter(attackRC, pos.x + 90, pos.y - 40, 80, 40); //��Ʈ ����
	}

	else if (animationFrame < 10 && animationFrame > 5)
	{
		attackRCactivated = false;
		nowAttDamage = 0;

		SetRectAtCenter(attackRC, -10, -10, 20, 20); //��Ʈ �������

	}

	else if (animationFrame >= 10)
	{
		animationFrame = 0;
		_state = State::MOVE;
		canMove = true;
		actType = MOVE;

	}
}

void Ryo::SmallKick()
{
	if (animationFrame == 3) {
		attackRCactivated = true;
		nowAttDamage = bigAttDamage;

		SetRectAtCenter(attackRC, pos.x + 100, pos.y + 20, 60, 40); //��Ʈ ����
	}
	else
	{
		attackRCactivated = false;
		nowAttDamage = 0;
		SetRectAtCenter(attackRC, -10, -10, 20, 20); //��Ʈ �������
	}

	if (animationFrame >= 6)
	{
		animationFrame = 0;
		_state = State::MOVE;
		canMove = true;
		actType = MOVE;
	}
}

void Ryo::BigPunch()
{
}

void Ryo::SmallPunch()
{
	if (animationFrame == 2) {
		attackRCactivated = true;
		nowAttDamage = bigAttDamage;

		SetRectAtCenter(attackRC, pos.x + 60, pos.y - 40, 20, 20); //��Ʈ ����
	}
	else
	{
		nowAttDamage = 0;
		SetRectAtCenter(attackRC, -10, -10, 20, 20); //��Ʈ �������
	}
	if (animationFrame >= 3)
	{
		animationFrame = 0;
		_state = State::MOVE;
		canMove = true;
		actType = MOVE;
		attackRCactivated = false;
	}
}
