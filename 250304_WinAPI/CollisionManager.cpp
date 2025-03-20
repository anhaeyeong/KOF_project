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
		pLeft->Release();
		delete pLeft;
		pLeft = nullptr;
	}
	if (pRight)
	{
		pLeft->Release();
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
	/*RECT atkrc = atkplayer->GetAttackRect();
	int atkdmg = atkplayer->GetDamage();
	if(atkplayer == pLeft)
	{
		RECT atkedrc = pRight->GetCharacterRect();
		if (RectInRect(atkrc, atkedrc))
		{
			if (pRight->GetState() != State::ATTACKED)
			{
				pRight->SetHP(pRight->GetHP() - atkdmg);
				pRight->SetState(State::ATTACKED);
			}
		}
		
	}
	if (atkplayer == pRight)
	{
		RECT atkedrc = pLeft->GetCharacterRect();
		if (RectInRect(atkrc, atkedrc))
		{
			if (pLeft->GetState() != State::ATTACKED)
			{
				pLeft->SetHP(pLeft->GetHP() - atkdmg);
				pLeft->SetState(State::ATTACKED);
			}
		}
	}*/
}

bool CollisionManager::isValidMove()
{
	/*RECT rcLeft = pLeft->GetRect();
	RECT rcRight = pRight->GetRect();
	if (RectInRect(rcLeft, rcRight))
	{
		if (pLeft->GetState() == State::MOVE &&
			pRight->GetState() == State::IDLE)
		{
			pRight->Move(pLeft->GetSpeed(), 0);
		}
		else if (pLeft->GetState() == State::IDLE &&
			pRight->GetState() == State::MOVE)
		{
			pLeft->Move(-pRight->GetSpeed(), 0);
		}
		else
		{
			return false;
		}

	}
	else
		return false;*/
    return false;
}
