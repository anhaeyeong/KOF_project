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
	/*RECT atkRC = atkplayer.GetAttackRC();
	RECT atkedRC = atkedplayer.GetCharacterRC();
	int atkDmg = atkplayer.GetDamage();
	if (RectInRect(atkRC, atkedRC))
	{
		if (atkedplayer.GetState() == State::GUARD)
		{
			if(atkplayer.isFilp)
				atkedplayer.Move(-2, 0);
			else
				atkedplayer.Move(2, 0);
			return false;
		}

		else
		{
			if(atkedplayer.GetState() == State::ATTACK)
			{
				atkedplayer.SetHP(atkedplayer.GetHP() - atkDmg * 2);
			}
			else
				atkedplayer.SetHP(atkedplayer.GetHP() - atkDmg);
			return true;
		}

	}*/
	 

    return false;
}

bool CollisionManager::isValidMove()
{
	//RECT rcLeft = pLeft->GetCharacterRC();
	//RECT rcRight = pRight->GetCharacterRC();
	//if (RectInRect(rcLeft, rcRight))
	//{
	//	// ������ �����̰� ������ ���������� ������
	//	if (pLeft->GetState() == State::MOVE &&
	//		pRight->GetState() == State::IDLE)
	//	{
	//		pRight->Move(pLeft->GetSpeed(), 0);
	//		return true;
	//	}
	//	// �������� �����̰� ������ �������� ������
	//	else if (pRight->GetState() == State::MOVE &&
	//		pLeft->GetState() == State::IDLE)
	//	{
	//		pLeft->Move(-pRight->GetSpeed(), 0);
	//		return true;
	//	}
	//	// �Ѵ� �����̰� ������ ������ ���缭�� ��.
	//	else
	//	{
	//		return false;
	//	}
	//}
	//else
	//	return true;
	return true;
}
