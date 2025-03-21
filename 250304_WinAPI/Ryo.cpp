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
	team = Team::LEFT;
	pos.x = WINSIZE_X - 700;
	pos.y = WINSIZE_Y - 150;
	width = 100;
	height = 200;
	characterRC = GetRectAtCenter(pos.x, pos.y, width, height);
	animationFrame = 0;
	maxIdleFrame = 10;
	maxAttackedFrame = 9;
	maxGuardFrame = 4;
	speed = 10;
	isFlip = false;
	isLeft = true;
	_state = State::IDLE;
	actType = IDLE;
	canMove = true;

	//animImages.resize(9);
	Image* idleImage = new Image();
	if (FAILED(idleImage->Init(TEXT("Image/Ryo_idle.bmp"), 2417, 300, 10, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Ryo_idle.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(idleImage);
	Image* moveFowardImage = new Image();
	if (FAILED(moveFowardImage->Init(TEXT("Image/Ryo_Smove_Front.bmp"), 1097, 300, 6, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Ryo_Smove_Front.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(moveFowardImage);

	Image* moveBackwardImage = new Image();
	if (FAILED(moveBackwardImage->Init(TEXT("Image/Ryo_Smove_Back.bmp"), 1047, 305, 6, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Ryo_Smove_Back.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(moveBackwardImage); //Ryo_fall_down
	Image* deadImage = new Image();
	if (FAILED(deadImage->Init(TEXT("Image/Ryo_fall_down.bmp"), 1278, 111, 9, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Ryo_fall_down.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(deadImage);
	//animImages.push_back(nullptr);
	Image* bigKickImage = new Image();
	if (FAILED(bigKickImage->Init(TEXT("Image/Ryo_high_kick.bmp"), 3843, 370, 10, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Ryo_high_kick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(bigKickImage);
	Image* smallKickImage = new Image();
	if (FAILED(smallKickImage->Init(TEXT("Image/Ryo_middle_kick.bmp"), 2485, 360, 6, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Ryo_middle_kick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(smallKickImage);

	Image* bigPunch = new Image();
	if (FAILED(bigPunch->Init(TEXT("Image/Ryo_big_punch.bmp"), 2485, 360, 6, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Ryo_big_punch.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(bigPunch);
	Image* smallPunchImage = new Image();
	if (FAILED(smallPunchImage->Init(TEXT("Image/Ryo_small_punch.bmp"), 906, 300, 3, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Ryo_small_punch.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(smallPunchImage);

	Image* guardImage = new Image();
	if (FAILED(guardImage->Init(TEXT("Image/ryo_block.bmp"), 1281, 300, maxGuardFrame, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("ryo_block.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(guardImage);

	// animImages.resize(애니메이션 개수);
	// if(FAILED(animImages[AnimationType::IDLE].Init(~~~));

	attackRC = GetRectAtCenter(-10, -10, 10, 20); //렉트 조정
}

void Ryo::Render(HDC hdc)
{
	//if (!characterImage)	return;
	
	if (_state == State::IDLE)
		animImages[ActType::IDLE]->Render(hdc, pos.x, pos.y - 5, animationFrame, width + 50, height + 15, isFlip);
	if (_state == State::MOVE)
	{
		switch (actType) {
		case MOVE_F:
			animImages[ActType::MOVE_F]->Render(hdc, pos.x, pos.y - 5, animationFrame, width + 20, height + 20, isFlip);
			break;

		case MOVE_B:
			animImages[ActType::MOVE_B]->Render(hdc, pos.x, pos.y - 5, animationFrame, width + 20, height + 20, isFlip);
			break;
		}
	}

	if (_state == State::ATTACK)

	{
		switch (actType)
		{
		case BIG_KICK:
			animImages[ActType::BIG_KICK]->Render(hdc, pos.x + 40, pos.y - 30, animationFrame, width + 130, height + 65, isFlip);
			break;
		case SMALL_KICK:
			animImages[ActType::SMALL_KICK]->Render(hdc, pos.x + 55, pos.y - 32, animationFrame, width + 170, height + 70, isFlip);
			break;
		case BIG_PUNCH:
			animImages[ActType::BIG_PUNCH]->Render(hdc, pos.x, pos.y-5, animationFrame, width + 90, height + 35, isFlip);
			break;
		case SMALL_PUNCH:
			animImages[ActType::SMALL_PUNCH]->Render(hdc, pos.x + 30, pos.y-5, animationFrame, width + 110, height+20, isFlip);
			break;
		}
	}
	if (_state == State::ATTACKED)
	{
		animImages[ActType::DEAD]->Render(hdc, pos.x, pos.y - 5, animationFrame, width + 130, height + 15, !isFlip);
	}
	if (_state == State::DEAD)
	{
		animImages[ActType::DEAD]->Render(hdc, pos.x, pos.y - 5, animationFrame, width + 130, height + 15, !isFlip);
	}

	if (_state == State::GUARD)
	{
		animImages[ActType::GUARD]->Render(hdc, pos.x, pos.y - 5, animationFrame, (width + 100), height + 15, isFlip);
	}

	// state에 따른 이미지 렌더링
	// if(_state == ~~~) 
	//  animImages[AnimationType::~~~]->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
	// -> AnimationType도 필요없을수도? 그냥 animImages[State::~~]->Render() 가능해보임
	if (debugRender)
	{
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		RenderRect(hdc, characterRC);
		if (attackRCactivated == true)
			RenderRect(hdc, attackRC.left, attackRC.top, attackRC.right - attackRC.left, attackRC.top - attackRC.bottom);

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);
	}
}

void Ryo::Win(HDC hdc)
{

}

void Ryo::Move(int dir)
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

void Ryo::BigKick()
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

void Ryo::SmallKick()
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

void Ryo::BigPunch()
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

void Ryo::SmallPunch()
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
