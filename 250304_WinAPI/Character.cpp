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
		MessageBox(g_hWnd, TEXT("Image/Ryo_Smove_Front.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(characterImage);
	animImages.push_back(nullptr);
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
	animImages.push_back(nullptr);
	Image* smallPunchImage = new Image();
	if (FAILED(smallPunchImage->Init(TEXT("Image/Ryo_small_punch.bmp"), 906, 300, 3, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Ryo_small_punch.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	animImages.push_back(smallPunchImage);

	// animImages.resize(애니메이션 개수);
	// if(FAILED(animImages[AnimationType::IDLE].Init(~~~));

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
		switch (actType) {
		case BIG_KICK:
			BigKick();
			break;
		case SMALL_KICK:
			SmallKick();
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
	case State::ATTACKED:
		break;
	}

	if (KeyManager::GetInstance()->IsOnceKeyDown('U'))
	{
		if (_state == State::MOVE)
		{
			animationFrame = 0;
			_state = State::ATTACK;
			canMove = false;
			actType = SMALL_PUNCH;
		}
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown('I'))
	{
		if (_state == State::MOVE)
		{
			animationFrame = 0;
			_state = State::ATTACK;
			canMove = false;
			actType = BIG_PUNCH;
		}
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown('J'))
	{
		if (_state == State::MOVE)
		{
			animationFrame = 0;
			_state = State::ATTACK;
			canMove = false;
			actType = SMALL_KICK;
		}
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown('K'))
	{
		if (_state == State::MOVE)
		{
			animationFrame = 0;
			_state = State::ATTACK;
			canMove = false;
			actType = BIG_KICK;
		}
	}
	
}

void Character::Render(HDC hdc)
{
	//if (!characterImage)	return;
	
	if (_state == State::MOVE)
		animImages[ActType::MOVE]->Render(hdc, pos.x, pos.y, animationFrame, width, height, isFlip);

	if (_state == State::ATTACK)

	{
		switch (actType)
		{
		case BIG_KICK:
			animImages[ActType::BIG_KICK]->Render(hdc, pos.x+40, pos.y-18, animationFrame, width+100, height+25, isFlip);
			//bigKickImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		case SMALL_KICK:
			animImages[ActType::SMALL_KICK]->Render(hdc, pos.x + 30, pos.y - 20, animationFrame, width + 120, height + 35, isFlip);
			//bigKickImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		case SMALL_PUNCH:
			animImages[ActType::SMALL_PUNCH]->Render(hdc, pos.x, pos.y, animationFrame, width+50, height, isFlip);
			//smallPunchImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
			break;
		}
	}

	// state에 따른 이미지 렌더링
	// if(_state == ~~~) 
	//  animImages[AnimationType::~~~]->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
	// -> AnimationType도 필요없을수도? 그냥 animImages[State::~~]->Render() 가능해보임


		
	
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	if (debugRender)
		RenderRectAtCenter(hdc, pos.x - 20, pos.y, characterRC.right - characterRC.left, characterRC.bottom - characterRC.top);
	if(attackRCactivated==true)
		RenderRect(hdc, attackRC.left, attackRC.top, attackRC.right - attackRC.left, attackRC.top - attackRC.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
}

void Character::Release()
{
	/*if (characterImage)
	{
		characterImage->Release();
		delete characterImage;
		characterImage = nullptr;
	}*/
	/*if (animImages.size() > 0)
	{
		for (int i = 0; i < animImages.size(); i++)
		{
			animImages[i].Release();
		}
		animImages.clear();
	}*/
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

		SetRectAtCenter(attackRC, pos.x+90, pos.y - 40, 80, 40); //렉트 조정
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
		actType = MOVE;

	}
}
void Character::SmallKick()
{
	if (animationFrame == 3) {
		attackRCactivated = true;
		nowAttDamage = bigAttDamage;

		SetRectAtCenter(attackRC, pos.x + 100, pos.y + 20, 60, 40); //렉트 조정
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
		_state = State::MOVE;
		canMove = true;
		actType = MOVE;
	}
}

void Character::BigPunch()
{
}

void Character::SmallPunch()
{
	if (animationFrame == 2) {
		attackRCactivated = true;
		nowAttDamage = bigAttDamage;

		SetRectAtCenter(attackRC, pos.x + 60, pos.y - 40, 20, 20); //렉트 조정
	}
	else
	{
		nowAttDamage = 0;
		SetRectAtCenter(attackRC, -10, -10, 20, 20); //렉트 원래대로
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
