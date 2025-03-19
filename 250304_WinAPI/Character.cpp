#include "Character.h"
#include "CommonFunction.h"
#include "Image.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::Init()
{
	pos.x = WINSIZE_X - 700;
	pos.y = WINSIZE_Y - 100;
	width = 40;
	height = 100;
	characterRC = GetRectAtCenter(pos.x, pos.y, width, height);
	animationFrame = 0;
	speed = 10;
	isFlip = false;
	_state = State::MOVE;
	canMove = true;

	characterImage = new Image();
	if (FAILED(characterImage->Init(TEXT("Image/Ryo_Smove_Front.bmp"), 1097, 300, 6, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Ryo_Smove_Front.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	bigKickImage = new Image();
	if (FAILED(bigKickImage->Init(TEXT("Image/iori_kick.bmp"), 1170, 106, 10, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/iori_kick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	
	smallPunchImage = new Image();
	if (FAILED(smallPunchImage->Init(TEXT("Image/Iori_small_punch.bmp"), 440, 125, 5, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Iori_small_punch.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	attackRC = GetRectAtCenter(-10, -10, 10, 20); //렉트 조정
}

void Character::Update()
{
	switch (_state)
	{
	case State::MOVE:
		if (KeyManager::GetInstance()->IsStayKeyDown('D'))
		{
			Move(10, 0);
			//isFlip = false;
		}
		else if (KeyManager::GetInstance()->IsStayKeyDown('A'))
		{
			Move(-10, 0);
			//isFlip = true;
		}
		break;
	case State::ATTACK:
		animationFrame++;
		switch (attackType) {
		case BIG_KICK:
			BigKick();
			break;
		case SMALL_KICK:

			break;
		case BIG_PUNCH:

			break;
		case SMALL_PUNCH:
			SmallPunch();
			break;
		default:
			break;
		}
		break;
	}

	if (KeyManager::GetInstance()->IsOnceKeyDown('U'))
	{
		if (_state == State::MOVE)
		{
			animationFrame = 0;
			_state = State::ATTACK;
			canMove = false;
			attackType = BIG_KICK;
		}
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown('I'))
	{
		if (_state == State::MOVE)
		{
			animationFrame = 0;
			_state = State::ATTACK;
			canMove = false;
			attackType = SMALL_PUNCH;
		}
	}
	
}

void Character::Render(HDC hdc)
{
	if (!characterImage)	return;
	
	if (_state == State::MOVE)
		characterImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);

	if (_state == State::ATTACK)
	{
		switch (attackType)
		{
		case BIG_KICK:
			bigKickImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		case SMALL_PUNCH:
			smallPunchImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		}
	}

	
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	if (debugRender)
		RenderRectAtCenter(hdc, pos.x, pos.y, width, height);
	if(attackRCactivated==true)
		RenderRect(hdc, attackRC.left, attackRC.top, attackRC.right - attackRC.left, attackRC.top - attackRC.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
}

void Character::Release()
{
	if (characterImage)
	{
		characterImage->Release();
		delete characterImage;
		characterImage = nullptr;
	}
}

void Character::Move(int dx, int dy)
{
	if (canMove == false) return;
	if (animationFrame >= 5)	animationFrame = 0;
	pos.x += dx;
	pos.y += dy;
	animationFrame++;
}

void Character::BigKick()
{
	
	if (animationFrame >= 3 && animationFrame <= 5) {
		attackRCactivated = true;	
		nowAttDamage = bigAttDamage;

		SetRectAtCenter(attackRC, pos.x+42, pos.y, 40, 20); //렉트 조정
	}

	else if(animationFrame < 10 && animationFrame > 5)
	{
		attackRCactivated = false;
		nowAttDamage = 0;

		SetRectAtCenter(attackRC, -10, -10, 20, 20); //렉트 원래대로
		
	}

	else if (animationFrame >= 10)
	{
		animationFrame = 0;
		_state = State::MOVE;
		canMove = true;
		attackType = NONE;

	}
}

void Character::SmallKick()
{
}

void Character::BigPunch()
{
}

void Character::SmallPunch()
{
	if (animationFrame >= 2 && animationFrame <= 3) {
		attackRCactivated = true;
		nowAttDamage = bigAttDamage;

		SetRectAtCenter(attackRC, pos.x + 42, pos.y, 20, 20); //렉트 조정
	}

	else if (animationFrame < 5 && animationFrame > 3)
	{
		attackRCactivated = false;
		nowAttDamage = 0;

		SetRectAtCenter(attackRC, -10, -10, 20, 20); //렉트 원래대로

	}

	else if (animationFrame >= 5)
	{
		animationFrame = 0;
		_state = State::MOVE;
		canMove = true;
		attackType = NONE;

	}
}
