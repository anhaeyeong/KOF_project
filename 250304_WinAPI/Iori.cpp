#include "Iori.h"
#include "Image.h"
#include "CommonFunction.h"

Iori::Iori()
{
}

Iori::~Iori()
{
}

void Iori::Init()
{
	pos.x = WINSIZE_X - 700;
	pos.y = WINSIZE_Y - 150;
	width = 100;
	height = 200;
	characterRC = GetRectAtCenter(pos.x, pos.y, width, height);
	animationFrame = 0;
	maxIdlePrame = 9;
	speed = 10;
	isFlip = false;
	isLeft = true;
	_state = State::IDLE;
	canMove = true;

	//animImages.resize(9);
	Image* idleImage = new Image();
	if (FAILED(idleImage->Init(TEXT("Image/Iori_idle.bmp"), 612, 96, 9, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Iori_idle.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}
	animImages.push_back(idleImage);
	Image* characterImage = new Image();
	if (FAILED(characterImage->Init(TEXT("Image/Iori_move_Front.bmp"), 612, 104, 9, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Iori_move_Front.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}
	animImages.push_back(characterImage);
	animImages.push_back(nullptr);
	Image* bigKickImage = new Image();
	if (FAILED(bigKickImage->Init(TEXT("Image/Iori_high_kick.bmp"), 1400, 105, 10, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Iori_high_kick.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}
	animImages.push_back(bigKickImage);
	Image* smallKickImage = new Image();
	if (FAILED(smallKickImage->Init(TEXT("Image/Iori_middle_kick.bmp"), 720, 102, 6, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Iori_middle_kick.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}
	animImages.push_back(smallKickImage);

	Image* bigPunch = new Image();
	if (FAILED(bigPunch->Init(TEXT("Image/Iori_big_punch.bmp"), 1080, 114, 9, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Iori_big_punch.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}
	animImages.push_back(bigPunch);
	Image* smallPunchImage = new Image();
	if (FAILED(smallPunchImage->Init(TEXT("Image/Iori_small_punch.bmp"), 500, 98, 5, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Iori_small_punch.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}
	animImages.push_back(smallPunchImage);

	// animImages.resize(�ִϸ��̼� ����);
	// if(FAILED(animImages[AnimationType::IDLE].Init(~~~));

	attackRC = GetRectAtCenter(-10, -10, 10, 20); //��Ʈ ����
}

void Iori::Render(HDC hdc)
{
	//if (!characterImage)	return;
	if (_state == State::IDLE)
		animImages[ActType::IDLE]->Render(hdc, pos.x, pos.y - 15, animationFrame, width + 20, height + 30, isFlip);
	if (_state == State::MOVE)
		animImages[ActType::MOVE]->Render(hdc, pos.x, pos.y - 5, animationFrame, width + 10, height + 20, isFlip);

	if (_state == State::ATTACK)

	{
		switch (actType)
		{
		case BIG_KICK:
			animImages[ActType::BIG_KICK]->Render(hdc, pos.x + 50, pos.y - 15, animationFrame, width + 120, height + 30, isFlip);
			break;
		case SMALL_KICK:
			animImages[ActType::SMALL_KICK]->Render(hdc, pos.x + 60, pos.y - 10, animationFrame, width + 90, height + 20, isFlip);
			break;
		case BIG_PUNCH:
			animImages[ActType::BIG_PUNCH]->Render(hdc, pos.x + 40, pos.y - 15, animationFrame, width + 100, height + 30, isFlip);
			break;
		case SMALL_PUNCH:
			animImages[ActType::SMALL_PUNCH]->Render(hdc, pos.x + 20, pos.y - 10, animationFrame, width + 70, height + 20, isFlip);
			break;
		}
	}

	// state�� ���� �̹��� ������
	// if(_state == ~~~) 
	//  animImages[AnimationType::~~~]->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
	// -> AnimationType�� �ʿ��������? �׳� animImages[State::~~]->Render() �����غ���
	RenderEllipseAtCenter(hdc, pos.x, pos.y, 10, 10);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	if (debugRender)
		RenderRectAtCenter(hdc, pos.x, pos.y, characterRC.right - characterRC.left, characterRC.bottom - characterRC.top);
	if (attackRCactivated == true)
		RenderRect(hdc, attackRC.left, attackRC.top, attackRC.right - attackRC.left, attackRC.top - attackRC.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
}

void Iori::Move(int dir)
{
	_state = State::MOVE;
	if (canMove == false) return;
	if (animationFrame >= 5)	animationFrame = 0;
	pos.x += dir * speed;
	//pos.y += dy;
	animationFrame++;
}

void Iori::BigKick()
{
	if (animationFrame >= 3 && animationFrame <= 5) {
		attackRCactivated = true;
		nowAttDamage = bigAttDamage;

		SetRectAtCenter(attackRC, pos.x + 90, pos.y - 40, 120, 40); //��Ʈ ����
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
		_state = State::IDLE;
		canMove = true;
		actType = MOVE;

	}
}

void Iori::SmallKick()
{
	if (animationFrame == 3) {
		attackRCactivated = true;
		nowAttDamage = smallAttDamage;

		SetRectAtCenter(attackRC, pos.x + 100, pos.y, 140, 30); //��Ʈ ����
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
		_state = State::IDLE;
		canMove = true;
		actType = MOVE;
	}
}

void Iori::BigPunch()
{
	if (animationFrame >= 2 && animationFrame <= 4) {
		attackRCactivated = true;
		nowAttDamage = bigAttDamage;

		SetRectAtCenter(attackRC, pos.x + 40, pos.y - 10, 90, 40); //��Ʈ ����
	}

	else if (animationFrame < 6 && animationFrame > 4)
	{
		attackRCactivated = false;
		nowAttDamage = 0;

		SetRectAtCenter(attackRC, -10, -10, 20, 20); //��Ʈ �������
	}

	else if (animationFrame >= 6)
	{
		animationFrame = 0;
		_state = State::IDLE;
		canMove = true;
		actType = MOVE;
	}
}

void Iori::SmallPunch()
{
	if (animationFrame == 2) {
		attackRCactivated = true;
		nowAttDamage = smallAttDamage;

		SetRectAtCenter(attackRC, pos.x + 80, pos.y - 40, 100, 30); //��Ʈ ����
	}
	else
	{
		nowAttDamage = 0;
		SetRectAtCenter(attackRC, -10, -10, 20, 20); //��Ʈ �������
	}
	if (animationFrame >= 3)
	{
		animationFrame = 0;
		_state = State::IDLE;
		canMove = true;
		actType = MOVE;
		attackRCactivated = false;
	}
}
