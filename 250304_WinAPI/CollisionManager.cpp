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

void CollisionManager::set(Character* player, bool isLeft)
{
	if (isLeft)	pLeft = player;
	else pRight = player;
}

void CollisionManager::isAttacked(Character* atkplayer)
{
	if (!atkplayer->GetAttackActivated()) return;
	RECT atkRC = atkplayer->GetAttackRC();
	if (atkplayer == pLeft)
	{
		RECT atkedRC = pRight->GetCharacterRC();
		int atkDmg = pLeft->GetDamage();
		if (RectInRect(atkRC, atkedRC))
		{
			if (!pRight->GetIsAttacked() && pRight->GetState() != State::ATTACKED)
			{
				pRight->SetAnimationFrame(0);
				pRight->SetHP(pRight->GetCurHP() - atkDmg);
				pRight->SetState(State::ATTACKED);
				pRight->SetIsAttacked(true);
			}
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

bool CollisionManager::isValidMove(Character* movingPlayer)
{
	RECT rcLeft = pLeft->GetCharacterRC();
	RECT rcRight = pRight->GetCharacterRC();

	Character* otherPlayer = (movingPlayer == pLeft) ? pRight : pLeft;

	RECT movingRC = rcLeft;
	if (movingPlayer == pRight)
		movingRC = rcRight;
	
	if (movingPlayer == pLeft)
	{
		movingRC.left += movingPlayer->GetSpeed();
		movingRC.right += movingPlayer->GetSpeed();
	}
	else if (movingPlayer == pRight)
	{
		movingRC.left -= movingPlayer->GetSpeed();
		movingRC.right -= movingPlayer->GetSpeed();
	}

	if (RectInRect(movingRC, otherPlayer->GetCharacterRC()))
	{
		// 한 명이 이동 중이고, 다른 한 명이 IDLE이면 IDLE인 캐릭터를 밀어냄
		if (movingPlayer->GetState() == State::MOVE && otherPlayer->GetState() == State::IDLE)
		{
			if (otherPlayer == pRight)
				otherPlayer->MovedByEnemy();
			else if (otherPlayer == pLeft)
				otherPlayer->MovedByEnemy();
			return true;
		}
		// 동시에 이동 중이면 이동 불가
		else if (movingPlayer->GetState() == State::MOVE && otherPlayer->GetState() == State::MOVE)
		{
			return false;
		}
	}

	return true;
}


