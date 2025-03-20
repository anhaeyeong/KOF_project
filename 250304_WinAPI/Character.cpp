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
	switch (team)
	{
	case Team::LEFT:
		if (canMove)
		{
			if (KeyManager::GetInstance()->IsStayKeyDown('D'))
			{
				Move(1);
				switch (isFlip) {
				case true:
					actType = MOVE_B;
					break;
				case false:
					actType = MOVE_F;
					break;
				}
			}
			else if (KeyManager::GetInstance()->IsStayKeyDown('A'))
			{
				Move(-1);
				switch (isFlip) {
				case true:
					actType = MOVE_F;
					break;
				case false:
					actType = MOVE_B;
					break;
				}
			}
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
			case SMALL_PUNCH:
				SmallPunch();
				
				break;
			default:
				break;
			}
			break;
		case State::ATTACKED:
			//if(animationFrame == 0) canMove = false;
			animationFrame++;
			
			if (animationFrame >= 12)
			{
				animationFrame = 0;
				_state = State::IDLE;
				SetIsAttacked(false);
				canMove = true;
			}
			break;
		default:
			break;
		}


		if (KeyManager::GetInstance()->IsOnceKeyDown('U'))
		{
			if (_state == State::MOVE || _state == State::IDLE)
			{
				animationFrame = 0;
				_state = State::ATTACK;
				canMove = false;
				actType = SMALL_PUNCH;
			}
		}
		if (KeyManager::GetInstance()->IsOnceKeyDown('I'))
		{
			if (_state == State::MOVE || _state == State::IDLE)
			{
				animationFrame = 0;
				_state = State::ATTACK;
				canMove = false;
				actType = BIG_PUNCH;
			}
		}
		if (KeyManager::GetInstance()->IsOnceKeyDown('J'))
		{
			if (_state == State::MOVE || _state == State::IDLE)
			{
				animationFrame = 0;
				_state = State::ATTACK;
				canMove = false;
				actType = SMALL_KICK;
			}
		}
		if (KeyManager::GetInstance()->IsOnceKeyDown('K'))
		{
			if (_state == State::MOVE || _state == State::IDLE)
			{
				animationFrame = 0;
				_state = State::ATTACK;
				canMove = false;
				actType = BIG_KICK;
			}
		}

		break;
	case Team::RIGHT:
		if (canMove)
		{
			if (KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT))
			{
					
				Move(1);
				switch (isFlip) {
				case true:
					actType = MOVE_B;
					break;
				case false:
					actType = MOVE_F;
					break;
				}
			}
			else if (KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT))
			{
				
				Move(-1);
				switch (isFlip) {
				case true:
					actType = MOVE_F;
					break;
				case false:
					actType = MOVE_B;
					break;
				}
			}
		}
		switch (_state)
		{
		case State::IDLE:
			animationFrame++;
			if (animationFrame >= maxIdlePrame)	animationFrame = 0;
			break;
		case State::MOVE:
			if (KeyManager::GetInstance()->IsOnceKeyUp(VK_RIGHT) || KeyManager::GetInstance()->IsOnceKeyUp(VK_LEFT))
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
			case SMALL_PUNCH:
				SmallPunch();
				
				break;
			default:
				break;
			}
			break;
		case State::ATTACKED:
			//if (animationFrame == 0) canMove = false;
			animationFrame++;

			if (animationFrame >= 12)
			{
				animationFrame = 0;
				_state = State::IDLE;
				SetIsAttacked(false);
				canMove = true;
			}
			break;
		default:
			break;
		}


		if (KeyManager::GetInstance()->IsOnceKeyDown(VK_NUMPAD5))
		{
			if (_state == State::MOVE || _state == State::IDLE)
			{
				animationFrame = 0;
				_state = State::ATTACK;
				canMove = false;
				actType = SMALL_PUNCH;
			}
		}
		if (KeyManager::GetInstance()->IsOnceKeyDown(VK_NUMPAD6))
		{
			if (_state == State::MOVE || _state == State::IDLE)
			{
				animationFrame = 0;
				_state = State::ATTACK;
				canMove = false;
				actType = BIG_PUNCH;
			}
		}
		if (KeyManager::GetInstance()->IsOnceKeyDown(VK_NUMPAD2))
		{
			if (_state == State::MOVE || _state == State::IDLE)
			{
				animationFrame = 0;
				_state = State::ATTACK;
				canMove = false;
				actType = SMALL_KICK;
			}
		}
		if (KeyManager::GetInstance()->IsOnceKeyDown(VK_NUMPAD3))
		{
			if (_state == State::MOVE || _state == State::IDLE)
			{
				animationFrame = 0;
				_state = State::ATTACK;
				canMove = false;
				actType = BIG_KICK;
			}
		}

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
	if (animImages.size() > 0)
	{
		for (int i = 0; i < animImages.size(); i++)
		{
			animImages[i]->Release();
		}
		animImages.clear();
	}
}

void Character::Move(int dir)
{
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

void Character::SetHP(int hp)
{
	this->hp = hp;
	if(team == Team::LEFT)
		UIManager::GetInstance()->UpdateHP(false, hp);
	if (team == Team::RIGHT)
		UIManager::GetInstance()->UpdateHP(true, hp);
	
}

void Character::MovedByEnemy()
{
	if (team == Team::LEFT)
	{
		pos.x -= speed;
		SetRectAtCenter(characterRC, pos.x, pos.y, width, height);
	}
	else if (team == Team::RIGHT)
	{
		pos.x += speed;
		SetRectAtCenter(characterRC, pos.x, pos.y, width, height);
	}
}
