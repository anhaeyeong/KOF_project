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
				if (pRight->GetActType() != MOVE_B) {
					pRight->SetCanMove(false);
					pRight->SetAnimationFrame(0);
					pRight->SetHP(pRight->GetCurHP() - atkDmg);
					pRight->SetState(State::ATTACKED);
					pRight->SetIsAttacked(true);
				}
				else
				{
					pRight->SetCanMove(false);
					pRight->SetAnimationFrame(0);;
					pRight->SetState(State::GUARD);
					pRight->SetIsAttacked(true);
				}
				
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
				if (pLeft->GetActType() != MOVE_B) {
					pLeft->SetCanMove(false);
					pLeft->SetAnimationFrame(0);
					pLeft->SetHP(pRight->GetCurHP() - atkDmg);
					pLeft->SetState(State::ATTACKED);
					pLeft->SetIsAttacked(true);
				}
				else
				{
					pLeft->SetCanMove(false);
					pLeft->SetAnimationFrame(0);;
					pLeft->SetState(State::GUARD);
					pLeft->SetIsAttacked(true);
				}
				
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
		// �� ���� �̵� ���̰�, �ٸ� �� ���� IDLE�̸� IDLE�� ĳ���͸� �о
		if (movingPlayer->GetState() == State::MOVE && otherPlayer->GetState() == State::IDLE)
		{
			if (otherPlayer == pRight)
				otherPlayer->MovedByEnemy();
			else if (otherPlayer == pLeft)
				otherPlayer->MovedByEnemy();
			return true;
		}
		// ���ÿ� �̵� ���̸� �̵� �Ұ�
		else if (movingPlayer->GetState() == State::MOVE && otherPlayer->GetState() == State::MOVE)
		{
			if (movingPlayer->GetDirection() == otherPlayer->GetDirection())
				return true;
			return false;
		}
	}

	return true;
}


