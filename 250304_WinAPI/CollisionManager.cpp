#include "CollisionManager.h"
#include "Character.h"

HRESULT CollisionManager::Init(Character* pLeft, Character* pRight)
{
	this->pLeft = pLeft;
	this->pRight = pRight;
	if (!this->pLeft)
		return E_FAIL;
	if (!this->pRight)
		return E_FAIL;
	return S_OK;
}

void CollisionManager::Release()
{
	if (pLeft)
	{
		delete pLeft;
		pLeft = nullptr;
	}
	if (pRight)
	{
		delete pRight;
		pRight = nullptr;
	}
	ReleaseInstance();
}

void CollisionManager::set(Character* player)
{
}

void CollisionManager::isAttacked(Character* atkplayer)
{
	RECT atkRC = atkplayer->GetAttackRC();
	if (atkplayer == pLeft)
	{
		RECT atkedRC = pRight->GetCharacterRC();
		int atkDmg = pLeft->GetDamage();
		if (RectInRect(atkRC, atkedRC))
		{
			if (pRight->GetState() != State::ATTACKED)
			{
				pRight->SetHP(pRight->GetCurHP() - atkDmg);
				pRight->SetState(State::ATTACKED);
			}
			else
			{
				
			}
		}
		
	}
	else if (atkplayer == pRight)
	{
		RECT atkedRC = pLeft->GetCharacterRC();
		int atkDmg = pRight->GetDamage();
		if (RectInRect(atkRC, atkedRC))
		{
			if (pLeft->GetState() != State::ATTACKED)
			{
				pLeft->SetHP(pLeft->GetCurHP() - atkDmg);
				pLeft->SetState(State::ATTACKED);
			}
			else
			{
				
			}
		}
	}
	
}

bool CollisionManager::isValidMove()
{
	RECT rcLeft = pLeft->GetCharacterRC();
	RECT rcRight = pRight->GetCharacterRC();
	if (RectInRect(rcLeft, rcRight))
	{
		return false;
	}
    return true;
}

void CollisionManager::MoveByEnemy(Character* player)
{
}
