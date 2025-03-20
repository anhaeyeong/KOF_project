#include "Clark.h"
#include "Image.h"
#include "CommonFunction.h"


void Clark::Init()
{
	team = Team::RIGHT;
	pos.x = WINSIZE_X - 300;
	pos.y = WINSIZE_Y - 150;
	width = 160;
	height = 230;
	characterRC = GetRectAtCenter(pos.x, pos.y, 100, 200);
	animationFrame = 0;
	speed = 10;
	isFlip = true;
	isLeft = true;
	_state = State::MOVE;
	canMove = true;

	//animImages.resize(9);
	animImages.push_back(nullptr);
	Image* characterImage = new Image();
	if (FAILED(characterImage->Init(TEXT("Image/Clark_Smove_Front.bmp"), 1608, 300, 7, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Clark_Smove_Front.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(characterImage);

	animImages.push_back(nullptr);

	Image* bigKickImage = new Image();
	if (FAILED(bigKickImage->Init(TEXT("Image/Clark_Highkick.bmp"), 5737, 356, 16, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Clark_Highkick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(bigKickImage);

	Image* smallKickImage = new Image();
	if (FAILED(smallKickImage->Init(TEXT("Image/Clark_Middlekick.bmp"), 1401, 300, 4, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Clark_Middlekick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(smallKickImage);

	Image* bigPunchImage = new Image();
	if (FAILED(bigPunchImage->Init(TEXT("Image/Clark_Spunch.bmp"), 2870, 356, 8, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Clark_Spunch.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(bigPunchImage);

	Image* smallPunchImage = new Image();
	if (FAILED(smallPunchImage->Init(TEXT("Image/Clark_Wpunch.bmp"), 1917, 300, 5, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Clark_Wpunch.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(smallPunchImage);

	// animImages.resize(애니메이션 개수);
	// if(FAILED(animImages[AnimationType::IDLE].Init(~~~));

	attackRC = GetRectAtCenter(-10, -10, 10, 20); //렉트 조정
}

void Clark::Render(HDC hdc)
{
	if (_state == State::MOVE)
		animImages[ActType::MOVE]->Render(hdc, pos.x-30, pos.y-5, animationFrame, width, height, isFlip);

	if (_state == State::ATTACK)

	{
		switch (actType)
		{
		case BIG_KICK:
			animImages[ActType::BIG_KICK]->Render(hdc, pos.x + 40, pos.y - 18, animationFrame, 
				width*animImages[ActType::BIG_KICK]->GetImageInfo()->frameWidth/ animImages[ActType::MOVE]->GetImageInfo()->frameWidth, 
				height* animImages[ActType::BIG_KICK]->GetImageInfo()->frameHeight / animImages[ActType::MOVE]->GetImageInfo()->frameHeight, 
				isFlip);
			//bigKickImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		case SMALL_KICK:
			animImages[ActType::SMALL_KICK]->Render(hdc, pos.x-80, pos.y +5, animationFrame, 
				width * animImages[ActType::SMALL_KICK]->GetImageInfo()->frameWidth / animImages[ActType::MOVE]->GetImageInfo()->frameWidth,
				height * animImages[ActType::SMALL_KICK]->GetImageInfo()->frameHeight / animImages[ActType::MOVE]->GetImageInfo()->frameHeight,
				isFlip);
			//bigKickImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		case BIG_PUNCH:
			animImages[ActType::BIG_PUNCH]->Render(hdc, pos.x - 60, pos.y-20, animationFrame,
				width * animImages[ActType::BIG_PUNCH]->GetImageInfo()->frameWidth / animImages[ActType::MOVE]->GetImageInfo()->frameWidth,
				(height * animImages[ActType::BIG_PUNCH]->GetImageInfo()->frameHeight / animImages[ActType::MOVE]->GetImageInfo()->frameHeight)-5,
				isFlip);
			//bigKickImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		case SMALL_PUNCH:
			animImages[ActType::SMALL_PUNCH]->Render(hdc, pos.x -62, pos.y, animationFrame,
				width * animImages[ActType::SMALL_PUNCH]->GetImageInfo()->frameWidth / animImages[ActType::MOVE]->GetImageInfo()->frameWidth,
				height * animImages[ActType::SMALL_PUNCH]->GetImageInfo()->frameHeight / animImages[ActType::MOVE]->GetImageInfo()->frameHeight,
				isFlip);
			//smallPunchImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		}
	}

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	if (debugRender)
		RenderRectAtCenter(hdc, pos.x - 20, pos.y, characterRC.right - characterRC.left, characterRC.bottom - characterRC.top);
	if (attackRCactivated == true && debugRender == true)
		RenderRect(hdc, attackRC.left, attackRC.top, attackRC.right - attackRC.left, attackRC.top - attackRC.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
}

void Clark::BigKick()
{
	if (isFlip == true) {
		pos.x-=17;
	}
	else pos.x +=17;

	if (animationFrame >= 5 && animationFrame <= 7) {
		attackRCactivated = true;
		nowAttDamage = bigAttDamage;

		if (isFlip == true) {
			SetRectAtCenter(attackRC, pos.x - 40, pos.y - 70, 80, 40); //렉트 조정
		}
		else SetRectAtCenter(attackRC, pos.x + 40, pos.y - 70, 80, 40); //렉트 조정
		
	}

	else if (animationFrame < 15 && animationFrame > 7)
	{
		attackRCactivated = false;
		nowAttDamage = 0;

		SetRectAtCenter(attackRC, -10, -10, 20, 20); //렉트 원래대로

	}

	else if (animationFrame >= 15)
	{
		animationFrame = 0;
		_state = State::MOVE;
		canMove = true;
		actType = MOVE;

	}
	
	
}

void Clark::SmallKick()
{
	if (animationFrame >= 1 && animationFrame <= 2) {
		attackRCactivated = true;
		nowAttDamage = smallAttDamage;

		switch (isFlip) {
		case true:
			SetRectAtCenter(attackRC, pos.x - 70, pos.y, 30, 40); //렉트 조정
			break;
		case false:
			SetRectAtCenter(attackRC, pos.x + 85, pos.y - 40, 70, 30); //렉트 조정
			break;
		}

		
	}
	else
	{
		attackRCactivated = false;
		nowAttDamage = 0;
		SetRectAtCenter(attackRC, -10, -10, 20, 20); //렉트 원래대로
	}

	if (animationFrame >= 3)
	{
		animationFrame = 0;
		_state = State::MOVE;
		canMove = true;
		actType = MOVE;
	}
}

void Clark::BigPunch()
{
	if (animationFrame >= 3 && animationFrame <= 5) {
		attackRCactivated = true;
		nowAttDamage = smallAttDamage;

		switch (isFlip) {
		case true:
			SetRectAtCenter(attackRC, pos.x - 110, pos.y - 40, 70, 30); //렉트 조정
			break;
		case false:
			SetRectAtCenter(attackRC, pos.x + 110, pos.y - 40, 70, 30); //렉트 조정
			break;
		}

	}
	else
	{
		nowAttDamage = 0;
		SetRectAtCenter(attackRC, -10, -10, 20, 20); //렉트 원래대로
	}
	if (animationFrame >= 7)
	{
		animationFrame = 0;
		_state = State::MOVE;
		canMove = true;
		actType = MOVE;
		attackRCactivated = false;
	}
}

void Clark::SmallPunch()
{
	if (animationFrame >=2&& animationFrame <=3) {
		attackRCactivated = true;
		nowAttDamage = smallAttDamage;

		switch (isFlip) {
		case true:
			SetRectAtCenter(attackRC, pos.x - 85, pos.y - 40, 70, 30); //렉트 조정
			break;
		case false:
			SetRectAtCenter(attackRC, pos.x + 85, pos.y - 40, 70, 30); //렉트 조정
			break;
		}
		
	}
	else
	{
		nowAttDamage = 0;
		SetRectAtCenter(attackRC, -10, -10, 20, 20); //렉트 원래대로
	}
	if (animationFrame >= 5)
	{
		animationFrame = 0;
		_state = State::MOVE;
		canMove = true;
		actType = MOVE;
		attackRCactivated = false;
	}
}
