#include "CollisionManager.h"

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
	// RECT atkRC = atkplayer.GetRect();
	// RECT atkedRC = atkedplayer.GetRect();
	// int atkDmg = atkplayer.GetDamage();
	// if(RectInRect(atkRC, atkedRC))
	//  if(atkedplayer.GetState() == STATE::DEFENSE)
	//		����ó�� x
	//	else
	//		�ǰ�ó��
	//		atkedĳ���� hp ������Ʈ
	//		return true;
	//  
    return false;
}

bool CollisionManager::isValidMove()
{
	//RECT rcLeft = pLeft.GetRect();
	//RECT rcRight = pRight.GetRect();
	//if (RectInRect(rcLeft, rcRight))
	// return false;
	//else
	// return true;
    return false;
}
