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
	team = Team::LEFT;
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
	maxGuardFrame = 5; //임시임

	//animImages.resize(9);
	Image* idleImage = new Image();
	if (FAILED(idleImage->Init(TEXT("Image/Iori_idle.bmp"), 612, 96, 9, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Iori_idle.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(idleImage);
	
	Image* characterImage = new Image();
	if (FAILED(characterImage->Init(TEXT("Image/Iori_move_Front.bmp"), 612, 104, 9, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Iori_move_Front.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	
	animImages.push_back(characterImage);
	Image* characterImage_b = new Image();
	if (FAILED(characterImage_b->Init(TEXT("Image/Iori_move_Back.bmp"), 630, 106, 9, 1, true, RGB(255, 0, 254))))
	{
		MessageBox(g_hWnd, TEXT("Image/Iori_move_Back.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	animImages.push_back(characterImage_b);

	Image* deadImg = new Image();
	if (FAILED(deadImg->Init(TEXT("Image/Iori_Dead.bmp"), 1410, 112, 10, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Iori_Dead.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	animImages.push_back(deadImg);

	Image* bigKickImage = new Image();
	if (FAILED(bigKickImage->Init(TEXT("Image/Iori_high_kick.bmp"), 1400, 105, 10, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Iori_high_kick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(bigKickImage);

	Image* smallKickImage = new Image();
	if (FAILED(smallKickImage->Init(TEXT("Image/Iori_middle_kick.bmp"), 720, 102, 6, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Iori_middle_kick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(smallKickImage);

	Image* bigPunch = new Image();
	if (FAILED(bigPunch->Init(TEXT("Image/Iori_big_punch.bmp"), 1080, 114, 9, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Iori_big_punch.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(bigPunch);

	Image* smallPunchImage = new Image();
	if (FAILED(smallPunchImage->Init(TEXT("Image/Iori_small_punch.bmp"), 500, 98, 5, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Iori_small_punch.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(smallPunchImage);

	Image* guardImage = new Image();
	if (FAILED(guardImage->Init(TEXT("Image/Iori_idle.bmp"), 612, 96, 9, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Iori_idle.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(guardImage);


	Image* hitImg = new Image();
	if (FAILED(hitImg->Init(TEXT("Image/Iori_hit.bmp"), 360, 100, 4, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Iori_small_punch.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(hitImg);

	// animImages.resize(애니메이션 개수);
	// if(FAILED(animImages[AnimationType::IDLE].Init(~~~));

	attackRC = GetRectAtCenter(-10, -10, 10, 20); //렉트 조정
}

void Iori::Render(HDC hdc)
{
	//if (!characterImage)	return;
	if (_state == State::IDLE)
		animImages[ActType::IDLE]->Render(hdc, pos.x, pos.y - 15, animationFrame, width + 20, height + 30, isFlip);
	if (_state == State::MOVE)
	{
		switch (actType) {
		case MOVE_F:
			animImages[ActType::MOVE_F]->Render(hdc, pos.x, pos.y - 5, animationFrame, width + 10, height + 20, isFlip);
			break;

		case MOVE_B:
			animImages[ActType::MOVE_B]->Render(hdc, pos.x, pos.y - 5, animationFrame, width + 10, height + 20, isFlip);
			break;
		}
	}

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

	if (_state == State::GUARD)

	{
		animImages[ActType::GUARD]->Render(hdc, pos.x, pos.y - 15, animationFrame, width + 20, height + 30, isFlip);
	}

	// state에 따른 이미지 렌더링
	// if(_state == ~~~) 
	//  animImages[AnimationType::~~~]->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
	// -> AnimationType도 필요없을수도? 그냥 animImages[State::~~]->Render() 가능해보임
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
	if (CollisionManager::GetInstance()->isValidMove(this))
	{
		pos.x += dir * speed;

	}
	SetRectAtCenter(characterRC, pos.x, pos.y, width, height);
	//pos.y += dy;
	animationFrame++;
}

void Iori::BigKick()
{
	if (animationFrame >= 3 && animationFrame <= 5) {
		if (!attackRCactivated)
		{
			attackRCactivated = true;
			nowAttDamage = bigAttDamage;

			SetRectAtCenter(attackRC, pos.x + 90, pos.y - 40, 120, 40); //렉트 조정
			CollisionManager::GetInstance()->isAttacked(this);
		}
	}

	else if (animationFrame < 10 && animationFrame > 5)
	{
		attackRCactivated = false;
		nowAttDamage = 0;

		SetRectAtCenter(attackRC, -10, -10, 20, 20); //렉트 원래대로

	}

	else if (animationFrame >= 10)
	{
		animationFrame = 0;
		_state = State::IDLE;
		canMove = true;
		actType = IDLE;

	}
}

void Iori::SmallKick()
{
	if (animationFrame == 3) {
		if (!attackRCactivated)
		{
			attackRCactivated = true;
			nowAttDamage = smallAttDamage;

			SetRectAtCenter(attackRC, pos.x + 100, pos.y, 140, 30); //렉트 조정

			CollisionManager::GetInstance()->isAttacked(this);
		}
	}
	else
	{
		attackRCactivated = false;
		nowAttDamage = 0;
		SetRectAtCenter(attackRC, -10, -10, 20, 20); //렉트 원래대로
	}

	if (animationFrame >= 6)
	{
		animationFrame = 0;
		_state = State::IDLE;
		canMove = true;
		actType = IDLE;
	}
}

void Iori::BigPunch()
{
	if (animationFrame >= 2 && animationFrame <= 4) {
		if (!attackRCactivated)
		{
			attackRCactivated = true;
			nowAttDamage = bigAttDamage;

			SetRectAtCenter(attackRC, pos.x + 40, pos.y - 10, 90, 40); //렉트 조정

			CollisionManager::GetInstance()->isAttacked(this);
		}
	}

	else if (animationFrame < 6 && animationFrame > 4)
	{
		attackRCactivated = false;
		nowAttDamage = 0;

		SetRectAtCenter(attackRC, -10, -10, 20, 20); //렉트 원래대로
	}

	else if (animationFrame >= 6)
	{
		animationFrame = 0;
		_state = State::IDLE;
		canMove = true;
		actType = IDLE;
	}
}

void Iori::SmallPunch()
{
	if (animationFrame == 2) {
		if (!attackRCactivated)
		{
			attackRCactivated = true;
			nowAttDamage = smallAttDamage;

			SetRectAtCenter(attackRC, pos.x + 80, pos.y - 40, 100, 30); //렉트 조정
			CollisionManager::GetInstance()->isAttacked(this);
		}
	}
	else
	{
		nowAttDamage = 0;
		SetRectAtCenter(attackRC, -10, -10, 20, 20); //렉트 원래대로
	}
	if (animationFrame >= 3)
	{
		animationFrame = 0;
		_state = State::IDLE;
		canMove = true;
		actType = IDLE;
		attackRCactivated = false;
	}
}
