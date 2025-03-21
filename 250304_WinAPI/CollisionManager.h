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
	void set(Character* player, bool isLeft); // 나중에 2대2 때 사용
	void isAttacked(Character* atkplayer);
	bool isValidMove(Character* movingPlayer);
	void MoveByEnemy(Character* otherPlayer);
};

