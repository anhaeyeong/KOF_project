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

}

void Character::Update()
{
	if (canMove)
	{
		if (KeyManager::GetInstance()->IsStayKeyDown('D'))
			Move(1);
		else if (KeyManager::GetInstance()->IsStayKeyDown('A'))
			Move(-1);
	}
	switch (_state)
	{
	case State::IDLE:
		animationFrame++;
		if (animationFrame >= maxIdlePrame)	animationFrame = 0;
		break;
	case State::MOVE:
		if (KeyManager::GetInstance()->IsOnceKeyUp('D') || KeyManager::GetInstance()->IsOnceKeyUp('A'))
		{
			animationFrame = 0;
			_state = State::IDLE;
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
			BigPunch();
			break;
		case State::ATTACKED:
			break;
		}
		break;
	case State::ATTACKED:
		break;
	default :
		break;
	}
	
	
	if (KeyManager::GetInstance()->IsOnceKeyDown('U'))
	{
		if (_state == State::MOVE || _state == State::IDLE)
		{
			if (_state == State::MOVE)
			{
				animationFrame = 0;
				_state = State::ATTACK;
				canMove = false;
				actType = SMALL_PUNCH;
			}
		}
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown('I'))
	{
		if (_state == State::MOVE || _state == State::IDLE)
		{
			if (_state == State::MOVE)
			{
				animationFrame = 0;
				_state = State::ATTACK;
				canMove = false;
				actType = BIG_PUNCH;
			}
		}
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown('J'))
	{
		if (_state == State::MOVE || _state == State::IDLE)
		{
			if (_state == State::MOVE)
			{
				animationFrame = 0;
				_state = State::ATTACK;
				canMove = false;
				actType = SMALL_KICK;
			}
		}
	}
	if (KeyManager::GetInstance()->IsOnceKeyDown('K'))
	{
		if (_state == State::MOVE || _state == State::IDLE)
		{
			if (_state == State::MOVE)
			{
				animationFrame = 0;
				_state = State::ATTACK;
				canMove = false;
				actType = BIG_KICK;
			}
		}
		break;
	case Team::RIGHT:
		switch (_state)
		{
		case State::MOVE:
			if (KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT))
			{
				Move(-1);
				//isFlip = false;
			}
			else if (KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT))
			{
				Move(1);
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
				BigPunch();
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

		if (KeyManager::GetInstance()->IsOnceKeyDown('V'))
		{
			if (_state == State::MOVE)
			{
				animationFrame = 0;
				_state = State::ATTACK;
				canMove = false;
				actType = SMALL_PUNCH;
			}
		}
		if (KeyManager::GetInstance()->IsOnceKeyDown('B'))
		{
			if (_state == State::MOVE)
			{
				animationFrame = 0;
				_state = State::ATTACK;
				canMove = false;
				actType = BIG_PUNCH;
			}
		}
		if (KeyManager::GetInstance()->IsOnceKeyDown('N'))
		{
			if (_state == State::MOVE)
			{
				animationFrame = 0;
				_state = State::ATTACK;
				canMove = false;
				actType = SMALL_KICK;
			}
		}
		if (KeyManager::GetInstance()->IsOnceKeyDown('M'))
		{
			if (_state == State::MOVE)
			{
				animationFrame = 0;
				_state = State::ATTACK;
				canMove = false;
				actType = BIG_KICK;
			}
		}
		break;
	default:

		break;

	}
	
}

void Character::Render(HDC hdc)
{
	
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

void Character::Move(int dir)
{
	if (canMove == false) return;
	if (animationFrame >= 5)	animationFrame = 0;
	pos.x += dir*speed;
	//pos.y += dy;
	animationFrame++;
}

void Character::BigKick()
{
	
	
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
