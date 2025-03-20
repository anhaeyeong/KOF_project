#pragma once
#include "Singleton.h"
#include "config.h"

using namespace std;

class Image;

class UIManager : public Singleton<UIManager>
{
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void SetPos(int index, int x, int y) { pos[index] = make_pair(x, y); }
	void UpdateHP(bool isLeft, int hp); // 수정	필요

private:
	HDC hdc;
	HDC backBuffer;
	HBITMAP backBufferBitmap;
	HBITMAP oldBitmap;

	Image* backGroundHP; // 체력바 배경
	Image* hpBar; // 체력바
	Image* player; // 캐릭터 얼굴

	pair<int, int> pos[2]{}; // 0: left, 1: right
	int hp[2]{100, 100}; // 0: left, 1: right
};

