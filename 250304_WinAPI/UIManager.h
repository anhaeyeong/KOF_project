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
	void UpdateHP(bool isLeft, int hp); // ����	�ʿ�

private:
	HDC hdc;
	HDC backBuffer;
	HBITMAP backBufferBitmap;
	HBITMAP oldBitmap;

	Image* backGroundHP; // ü�¹� ���
	Image* hpBar; // ü�¹�
	Image* player; // ĳ���� ��

	pair<int, int> pos[2]{}; // 0: left, 1: right
	int hp[2]{100, 100}; // 0: left, 1: right
};

