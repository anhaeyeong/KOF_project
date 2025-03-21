#include "Mai.h"
#include "Image.h"
#include "CommonFunction.h"

Mai::Mai()
{
}

Mai::~Mai()
{
}

void Mai::Init()
{
	team = Team::RIGHT;

	pos.x = WINSIZE_X - 300;
	pos.y = WINSIZE_Y - 150;
	width = 100;
	height = 200;
	characterRC = GetRectAtCenter(pos.x, pos.y, width, height);
	animationFrame = 0;
	maxIdlePrame = 12;
	speed = 10;
	isFlip = true;
	isLeft = true;
	_state = State::IDLE;
	actType = IDLE;
	canMove = true;

	//animImages.resize(9);
	//animImages.push_back(nullptr); // Idle
	Image* IdleImage = new Image();
	if (FAILED(IdleImage->Init(TEXT("Image/Mai_Endle.bmp"), 3000, 300, 12, 1, true, RGB(255, 0, 255)))) // 250, 300
	{
		MessageBox(g_hWnd, TEXT("Image/Mai_Endle.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(IdleImage);
	Image* moveFowardImage = new Image();
	if (FAILED(moveFowardImage->Init(TEXT("Image/Mai_Smove_Front.bmp"), 1901, 300, 6, 1, true, RGB(255, 0, 255)))) // 316, 300
	{
		MessageBox(g_hWnd, TEXT("Image/Mai_Smove_Front.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(moveFowardImage);

	Image* moveBackwardImage = new Image();
	if (FAILED(moveBackwardImage->Init(TEXT("Image/Mai_Smove_Back.bmp"), 1677, 300, 6, 1, true, RGB(255, 0, 255)))) // 316, 300
	{
		MessageBox(g_hWnd, TEXT("Mai_Smove_Back.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(moveBackwardImage);
	Image* deadImage = new Image(); // 실행 확인용 이미지 -> 마이로 수정해야함
	if (FAILED(deadImage->Init(TEXT("Image/Mai_dead.bmp"), 1300, 100, 10, 1, true, RGB(255, 0, 255)))) // 360, 412
	{
		MessageBox(g_hWnd, TEXT("Image/Mai_dead.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(deadImage); // Dead
	Image* bigKickImage = new Image();
	if (FAILED(bigKickImage->Init(TEXT("Image/Mai_Highkick.bmp"), 2163, 412, 6, 1, true, RGB(255, 0, 255)))) // 360, 412
	{
		MessageBox(g_hWnd, TEXT("Image/Mai_Highkick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(bigKickImage);
	Image* smallKickImage = new Image();
	if (FAILED(smallKickImage->Init(TEXT("Image/Mai_Middlekick.bmp"), 2249, 372, 6, 1, true, RGB(255, 0, 255)))) // 374, 372
	{
		MessageBox(g_hWnd, TEXT("Image/Mai_Middlekick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(smallKickImage);
	//animImages.push_back(nullptr); // High punch
	Image* HighPunchImage = new Image();
	if (FAILED(HighPunchImage->Init(TEXT("Image/Mai_Spunch.bmp"), 1634, 370, 5, 1, true, RGB(255, 0, 255)))) // 400,300
	{
		MessageBox(g_hWnd, TEXT("Mai_Spunch.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(HighPunchImage);
	Image* smallPunchImage = new Image();
	if (FAILED(smallPunchImage->Init(TEXT("Image/Mai_Wpunch.bmp"), 1600, 300, 4, 1, true, RGB(255, 0, 255)))) // 326, 370
	{
		MessageBox(g_hWnd, TEXT("Mai_Wpunch.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(smallPunchImage);
	animImages.push_back(nullptr);

	Image* attackedImage = new Image();
	if (FAILED(attackedImage->Init(TEXT("Image/Mai_Attacked.bmp"), 480, 99, 6, 1, true, RGB(255, 0, 255)))) // 326, 370
	{
		MessageBox(g_hWnd, TEXT("Mai_Attacked.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(attackedImage);

	// animImages.resize(애니메이션 개수);
	// if(FAILED(animImages[AnimationType::IDLE].Init(~~~));

	attackRC = GetRectAtCenter(-10, -10, 10, 20); //렉트 조정
}

void Mai::Render(HDC hdc)
{
	if (_state == State::IDLE)
	{
		animImages[ActType::IDLE]->Render(hdc, pos.x - 25, pos.y + 5, animationFrame, (width + 30), height - 10, !isFlip);
	}
	if (_state == State::MOVE)
	{
		switch (actType)
		{
		case MOVE_F:
			animImages[ActType::MOVE_F]->Render(hdc, pos.x - 25, pos.y + 5, animationFrame, (width + 85), height - 10, !isFlip);
			break;

		case MOVE_B:
			animImages[ActType::MOVE_B]->Render(hdc, pos.x - 25, pos.y + 5, animationFrame, (width + 85), height - 10, !isFlip);
			break;
		}
	}
		
	if (_state == State::ATTACK)

	{
		switch (actType)
		{
		case BIG_KICK:
			animImages[ActType::BIG_KICK]->Render(hdc, pos.x - 45, pos.y - 3, animationFrame, (width + 97), (height + 10), !isFlip);
			
			//bigKickImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		case SMALL_KICK:
			animImages[ActType::SMALL_KICK]->Render(hdc, pos.x - 50, pos.y - 8, animationFrame, (width + 93), (height + 20), !isFlip);
			
			//bigKickImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		case BIG_PUNCH:
			animImages[ActType::BIG_PUNCH]->Render(hdc, pos.x - 100, pos.y - 8, animationFrame, (width + 110), (height + 15), !isFlip);
			
			//bigKickImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		case SMALL_PUNCH:
			animImages[ActType::SMALL_PUNCH]->Render(hdc, pos.x - 70, pos.y + 2, animationFrame, (width + 90), (height - 5), !isFlip);
			
			//smallPunchImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		}
	}
	if (_state == State::ATTACKED)
	{
		animImages[ActType::ATTACKED]->Render(hdc, pos.x - 25, pos.y + 5, animationFrame, (width + 30), height - 10, isFlip);
	}
	if (_state == State::DEAD)
	{
		if (animationFrame < 10)
			animImages[ActType::DEAD]->Render(hdc, pos.x - 25, pos.y + 5, animationFrame, (width + 120), height + 10, isFlip);
	}

	// state에 따른 이미지 렌더링
	// if(_state == ~~~) 
	//  animImages[AnimationType::~~~]->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
	// -> AnimationType도 필요없을수도? 그냥 animImages[State::~~]->Render() 가능해보임

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	if (debugRender)
		RenderRectAtCenter(hdc, pos.x - 20, pos.y, characterRC.right - characterRC.left, characterRC.bottom - characterRC.top);
	if (attackRCactivated == true)
		RenderRect(hdc, attackRC.left, attackRC.top, attackRC.right - attackRC.left, attackRC.top - attackRC.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
}

void Mai::Move(int dir)
{
	_state = State::MOVE;

	if (canMove == false) return;
	_state = State::MOVE;
	if (animationFrame >= 5)
	{
		animationFrame = 0;
	}
	if (CollisionManager::GetInstance()->isValidMove(this))
	{
		pos.x += dir * speed;
		
	}
	SetRectAtCenter(characterRC, pos.x, pos.y, width, height);
	//pos.y += dy;
	animationFrame++;
}

void Mai::BigKick()
{
	if (animationFrame >= 3 && animationFrame <= 4) {
		if (!attackRCactivated)
		{
			attackRCactivated = true;
			nowAttDamage = bigAttDamage;
			SetRectAtCenter(attackRC, pos.x - 110, pos.y - 15, 80, 40); //렉트 조정
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

void Mai::SmallKick()
{

	if (animationFrame >= 1 && animationFrame <= 2) {
		if (!attackRCactivated)
		{
			attackRCactivated = true;
			nowAttDamage = smallAttDamage;

			SetRectAtCenter(attackRC, pos.x - 110, pos.y, 80, 40); //렉트 조정
			CollisionManager::GetInstance()->isAttacked(this);
		}
		
	}

	else if (animationFrame < 6 && animationFrame > 2)
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

void Mai::BigPunch()
{
	if (animationFrame >= 1 && animationFrame <= 2) {
		if (!attackRCactivated)
		{
			attackRCactivated = true;
			nowAttDamage = bigAttDamage;

			SetRectAtCenter(attackRC, pos.x - 150, pos.y + 70, 120, 60); //렉트 조정
			CollisionManager::GetInstance()->isAttacked(this);
		}
		
	}

	else if (animationFrame < 5 && animationFrame > 2)
	{
		attackRCactivated = false;
		nowAttDamage = 0;

		SetRectAtCenter(attackRC, -10, -10, 20, 20); //렉트 원래대로

	}

	else if (animationFrame >= 5)
	{
		animationFrame = 0;
		_state = State::IDLE;
		canMove = true;
		actType = IDLE;
	}
}

void Mai::SmallPunch()
{
	if (animationFrame >= 2 && animationFrame <= 3) {
		if (!attackRCactivated)
		{
			attackRCactivated = true;
			nowAttDamage = smallAttDamage;

			SetRectAtCenter(attackRC, pos.x - 120, pos.y + 20, 80, 40); //렉트 조정
			CollisionManager::GetInstance()->isAttacked(this);
		}
		
	}
	else if (animationFrame >= 4)
	{
		attackRCactivated = false;
		nowAttDamage = 0;

		SetRectAtCenter(attackRC, -10, -10, 20, 20); //렉트 원래대로
		animationFrame = 0;
		_state = State::IDLE;
		canMove = true;
		actType = IDLE;
	}
}
