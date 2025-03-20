#pragma once
#include "Singleton.h"
#include "config.h"
#include "commonFunction.h"

class Character;
class CollisionManager : public Singleton<CollisionManager>
{
private:
	Character* pLeft;
	Character* pRight;
public:
	HRESULT Init(Character* pLeft, Character* pRight);
	void Release();
	void set(Character* player); // ���߿� 2��2 �� ���
	void isAttacked(Character* atkplayer);
	bool isValidMove();

};

