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

bool CollisionManager::isAttacked(Character& atkplayer, Character& atkedplayer)
{
	/*RECT atkRC = atkplayer.GetRect();
	RECT atkedRC = atkedplayer.GetRect();
	int atkDmg = atkplayer.GetDamage();
	if (RectInRect(atkRC, atkedRC) && atkedplayer.GetState() != State::ATTACKED)
	{
		if (atkedplayer.GetState() == STATE::DEFENSE)
		{
			if (atkplayer.GetIsFilp())
			{
				atkedplayer.Move(-2, 0);
			}
			else
			{
				atkedplayer.Move(2, 0);
			}
			return false;
		}
		else
		{
			atkedplayer.SetHp(atkedplayer.GetHp() - atkDmg);
			atkedplayer.SetState(STATE::ATTACKED);

			return true;
		}
	}*/
    return false;
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
