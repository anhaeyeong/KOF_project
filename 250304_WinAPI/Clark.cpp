#include "Clark.h"
#include "Image.h"
#include "CommonFunction.h"


void Clark::Init()
{
	team = Team::RIGHT;
	pos.x = WINSIZE_X - 300;
	pos.y = WINSIZE_Y - 150;
	width = 165;
	height = 230;
	characterRC = GetRectAtCenter(pos.x, pos.y, 100, 200);
	animationFrame = 0;
	speed = 10;
	isFlip = true;
	isLeft = true;
	_state = State::IDLE;
	actType = IDLE;
	canMove = true;
	maxIdlePrame = 19;

	IsFlipToModifyingValue();


	animImages.reserve(9);
	Image* idleImage = new Image();
	if (FAILED(idleImage->Init(TEXT("Image/Clark_Endle.bmp"), 4565, 300, 19, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Clark_Endle.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(idleImage);

	Image* moveFowardImage = new Image();
	if (FAILED(moveFowardImage->Init(TEXT("Image/Clark_Smove_Front.bmp"), 1608, 300, 7, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Clark_Smove_Front.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(moveFowardImage);

	Image* moveBackwardImage = new Image();
	if (FAILED(moveBackwardImage->Init(TEXT("Image/Clark_Smove_Back.bmp"), 1581, 300, 7, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Clark_Smove_Back.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(moveBackwardImage);

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

	moveModifiedWidth = width * animImages[ActType::MOVE_F]->GetImageInfo()->frameWidth / animImages[ActType::IDLE]->GetImageInfo()->frameWidth;
	moveModifiedHeight = height * animImages[ActType::MOVE_F]->GetImageInfo()->frameHeight / animImages[ActType::IDLE]->GetImageInfo()->frameHeight;

	moveBModifiedWidth = width * animImages[ActType::MOVE_B]->GetImageInfo()->frameWidth / animImages[ActType::IDLE]->GetImageInfo()->frameWidth;
	moveBModifiedHeight = height * animImages[ActType::MOVE_B]->GetImageInfo()->frameHeight / animImages[ActType::IDLE]->GetImageInfo()->frameHeight;

	smallPunchModifiedWidth = width * animImages[ActType::SMALL_PUNCH]->GetImageInfo()->frameWidth / animImages[ActType::IDLE]->GetImageInfo()->frameWidth;
	smallPunchModifiedHeight = height * animImages[ActType::SMALL_PUNCH]->GetImageInfo()->frameHeight / animImages[ActType::IDLE]->GetImageInfo()->frameHeight;

	bigPunchModifiedWidth = width * animImages[ActType::BIG_PUNCH]->GetImageInfo()->frameWidth / animImages[ActType::IDLE]->GetImageInfo()->frameWidth;
	bigPunchModifiedHeight = (height * animImages[ActType::BIG_PUNCH]->GetImageInfo()->frameHeight / animImages[ActType::IDLE]->GetImageInfo()->frameHeight) - 5;

	smallKickModifiedWidth = width * animImages[ActType::SMALL_KICK]->GetImageInfo()->frameWidth / animImages[ActType::IDLE]->GetImageInfo()->frameWidth;
	smallKickModifiedHeight = height * animImages[ActType::SMALL_KICK]->GetImageInfo()->frameHeight / animImages[ActType::IDLE]->GetImageInfo()->frameHeight;

	bigKickModifiedWidth = width * animImages[ActType::BIG_KICK]->GetImageInfo()->frameWidth / animImages[ActType::IDLE]->GetImageInfo()->frameWidth;
	bigKickModifiedHeight = height * animImages[ActType::BIG_KICK]->GetImageInfo()->frameHeight / animImages[ActType::IDLE]->GetImageInfo()->frameHeight;
}

void Clark::Render(HDC hdc)
{
	if (_state == State::IDLE) {
		animImages[ActType::IDLE]->Render(hdc, pos.x + modifyingValue * idleModifiedX, pos.y - 5, animationFrame, width, height, isFlip);
		/*switch (isFlip) {
		case true:
			animImages[ActType::IDLE]->Render(hdc, pos.x - 30, pos.y - 5, animationFrame, width, height, isFlip);
			break;

		case false:
			animImages[ActType::IDLE]->Render(hdc, pos.x - 10, pos.y - 5, animationFrame, width, height, isFlip);
			break;
		}*/
	}
	if (_state == State::MOVE)
	{
		switch (actType)
		{
		case MOVE_F:
			animImages[ActType::MOVE_F]->Render(hdc, pos.x + modifyingValue * idleModifiedX, pos.y - 5, animationFrame,
				moveModifiedWidth,
				moveModifiedHeight,
				isFlip);
			break;
		case MOVE_B:
			animImages[ActType::MOVE_B]->Render(hdc, pos.x + modifyingValue * idleModifiedX, pos.y - 5, animationFrame,
				moveBModifiedWidth,
				moveBModifiedHeight,
				isFlip);
			break;
		}
	}

	if (_state == State::ATTACK)

	{
		switch (actType)
		{
		case BIG_KICK:
			animImages[ActType::BIG_KICK]->Render(hdc, pos.x +5 + modifyingValue * bigKickModifiedX, pos.y - 18, animationFrame,
				bigKickModifiedWidth,
				bigKickModifiedHeight,
				isFlip);
			//bigKickImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		case SMALL_KICK:
			animImages[ActType::SMALL_KICK]->Render(hdc, pos.x  + modifyingValue * smallKickModifiedX, pos.y, animationFrame,
				smallKickModifiedWidth,
				smallKickModifiedHeight,
				isFlip);
			//bigKickImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		case BIG_PUNCH:
			animImages[ActType::BIG_PUNCH]->Render(hdc, pos.x -5 + modifyingValue * bigPunchModifiedX, pos.y - 20, animationFrame,
				bigPunchModifiedWidth,
				bigPunchModifiedHeight,
				isFlip);
			//bigKickImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		case SMALL_PUNCH:
			animImages[ActType::SMALL_PUNCH]->Render(hdc, pos.x +7 + modifyingValue * smallPunchModifiedX, pos.y, animationFrame,
				smallPunchModifiedWidth,
				smallPunchModifiedHeight,
				isFlip);
			//smallPunchImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		}
	}

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	if (debugRender)
		RenderRect(hdc, characterRC);
	if (attackRCactivated == true && debugRender == true)
		RenderRect(hdc, attackRC.left, attackRC.top, attackRC.right - attackRC.left, attackRC.top - attackRC.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
}

void Clark::Move(int dir)
{
	_state = State::MOVE;
	if (canMove == false) return;

	if (animationFrame >= 6)	animationFrame = 0;
	pos.x += dir * speed;
	SetRectAtCenter(characterRC, pos.x, pos.y, 100, 200);

	//pos.y += dy;
	animationFrame++;
}

void Clark::BigKick()
{
	if (isFlip == true) {
		pos.x -= 17;
		SetRectAtCenter(characterRC, pos.x, pos.y, 100, 200);
	}
	else {
		pos.x += 17;
		SetRectAtCenter(characterRC, pos.x, pos.y, 100, 200);
	}

	if (animationFrame >= 5 && animationFrame <= 7) {
		attackRCactivated = true;
		nowAttDamage = bigAttDamage;

		if (isFlip == true) {
			SetRectAtCenter(attackRC, pos.x-70, pos.y - 70, 100, 40); //렉트 조정
		}
		else SetRectAtCenter(attackRC, pos.x + 90, pos.y - 70, 100, 40); //렉트 조정
		CollisionManager::GetInstance()->isAttacked(this);

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
		_state = State::IDLE;
		canMove = true;
		actType = IDLE;

	}


}

void Clark::SmallKick()
{
	if (animationFrame >= 1 && animationFrame <= 2) {
		attackRCactivated = true;
		nowAttDamage = smallAttDamage;

		switch (isFlip) {
		case true:
			SetRectAtCenter(attackRC, pos.x - 50, pos.y, 30, 40); //렉트 조정
			break;
		case false:
			SetRectAtCenter(attackRC, pos.x + 55, pos.y, 30, 40); //렉트 조정
			break;
		}
		CollisionManager::GetInstance()->isAttacked(this);


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
		_state = State::IDLE;
		canMove = true;
		actType = IDLE;
	}
}

void Clark::BigPunch()
{
	if (animationFrame >= 3 && animationFrame <= 5) {
		attackRCactivated = true;
		nowAttDamage = smallAttDamage;

		switch (isFlip) {
		case true:
			SetRectAtCenter(attackRC, pos.x - 90, pos.y - 40, 70, 30); //렉트 조정
			break;
		case false:
			SetRectAtCenter(attackRC, pos.x + 70, pos.y - 40, 70, 30); //렉트 조정
			break;
		}
		CollisionManager::GetInstance()->isAttacked(this);

	}
	else
	{
		nowAttDamage = 0;
		SetRectAtCenter(attackRC, -10, -10, 20, 20); //렉트 원래대로
	}
	if (animationFrame >= 7)
	{
		animationFrame = 0;
		_state = State::IDLE;
		canMove = true;
		actType = IDLE;
		attackRCactivated = false;
	}
}

void Clark::SmallPunch()
{
	if (animationFrame >= 2 && animationFrame <= 3) {
		attackRCactivated = true;
		nowAttDamage = smallAttDamage;

		switch (isFlip) {
		case true:
			SetRectAtCenter(attackRC, pos.x - 65, pos.y - 40, 70, 30); //렉트 조정
			break;
		case false:
			SetRectAtCenter(attackRC, pos.x + 80, pos.y - 40, 70, 30); //렉트 조정
			break;
		}
		CollisionManager::GetInstance()->isAttacked(this);

	}
	else
	{
		nowAttDamage = 0;
		SetRectAtCenter(attackRC, -10, -10, 20, 20); //렉트 원래대로
	}
	if (animationFrame >= 5)
	{
		animationFrame = 0;
		_state = State::IDLE;
		canMove = true;
		actType = IDLE;
		attackRCactivated = false;
	}
}
