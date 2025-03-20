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
	isLeft = true;
	_state = State::MOVE;
	canMove = true;

	characterImage = new Image();
	if (FAILED(characterImage->Init(TEXT("Image/iori_walk.bmp"), 612, 104, 9, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/iori_walk.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	bigKickImage = new Image();
	if (FAILED(bigKickImage->Init(TEXT("Image/iori_kick.bmp"), 1170, 106, 10, 1, true, RGB(169, 139, 150))))
	{
		MessageBox(g_hWnd, TEXT("Image/iori_kick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
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
		switch (attackType) {
		case BIG_KICK:
			BigKick();
			break;
		case SMALL_KICK:

			break;
		case BIG_PUNCH:

			break;
		case SMALL_PUNCH:

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
			attackType = BIG_KICK;
		}
	}
	
}

void Character::Render(HDC hdc)
{
	if (!characterImage)	return;
	
	if (_state == State::MOVE)
		characterImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);

	if (_state == State::ATTACK)
		bigKickImage->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
	// state에 따른 이미지 렌더링
	// if(_state == ~~~) 
	//  animImages[AnimationType::~~~]->Render(hdc, pos.x, pos.y, animationFrame, isFlip);
	// -> AnimationType도 필요없을수도? 그냥 animImages[State::~~]->Render() 가능해보임

		
	
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	if (debugRender)
		RenderRectAtCenter(hdc, pos.x, pos.y, width, height);
	if(attackRCactivated==true)
		RenderRect(hdc, attackRC.left, attackRC.top, 20, 20);

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
	if (animationFrame > 7)	animationFrame = 0;
	pos.x += dx;
	pos.y += dy;
	animationFrame++;
}

void Character::BigKick()
{
	
	if (animationFrame >= 3 && animationFrame <= 5) {
		attackRCactivated = true;	
		nowAttDamage = bigAttDamage;

		SetRectAtCenter(attackRC, pos.x+42, pos.y-21, 20, 20); //렉트 조정
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
}

void Character::isDead()
{
	if (_state != State::DEAD && nowHp <= 0)
	{
		_state = State::DEAD;
	}
}
