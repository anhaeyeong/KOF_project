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
	if (!atkplayer->GetAttackActivated()) return;
	RECT atkRC = atkplayer->GetAttackRC();
	if (atkplayer == pLeft)
	{
		RECT atkedRC = pRight->GetCharacterRC();
		int atkDmg = pLeft->GetDamage();
		if (!pRight->GetIsAttacked() && RectInRect(atkRC, atkedRC))
		{
			pRight->SetAnimationFrame(0);
			pRight->SetHP(pRight->GetCurHP() - atkDmg);
			pRight->SetState(State::ATTACKED);
			pRight->SetIsAttacked(true);
		}

	}
	else if (atkplayer == pRight)
	{
		RECT atkedRC = pLeft->GetCharacterRC();
		int atkDmg = pRight->GetDamage();
		if (RectInRect(atkRC, atkedRC))
		{
			if (!pLeft->GetIsAttacked() && pLeft->GetState() != State::ATTACKED)
			{
				pLeft->SetAnimationFrame(0);
				pLeft->SetHP(pLeft->GetCurHP() - atkDmg);
				pLeft->SetState(State::ATTACKED);
				pLeft->SetIsAttacked(true);
			}
		}
	}
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
