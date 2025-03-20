#include "UIManager.h"
#include "Image.h"

HRESULT UIManager::Init()
{
	backGroundHP = new Image();
	backGroundHP->Init(TEXT("Image/BackgroundHP.bmp"), 445, 35, true, RGB(255, 0, 191));

	hpBar = new Image();
	hpBar->Init(TEXT("Image/HPBar.bmp"), 445, 35, true, RGB(255, 0, 255));

	pos[0] = make_pair(50, 50);
	pos[1] = make_pair(WINSIZE_X - 50, 50);

	return S_OK;
}

void UIManager::Release()
{
	if (backGroundHP)
	{
		backGroundHP->Release();
		delete backGroundHP;
		backGroundHP = nullptr;
	}
	if (hpBar)
	{
		hpBar->Release();
		delete hpBar;
		hpBar = nullptr;
	}
}

void UIManager::Render(HDC hdc)
{
	backGroundHP->RenderUI(hdc, pos[0].first, pos[0].second, 445, 35);
	hpBar->RenderUI(hdc, pos[0].first, pos[0].second, 445*(hp[0]/100.0f), 35);

	backGroundHP->RenderUI(hdc, pos[1].first, pos[1].second, 445, 35, true);
	hpBar->RenderUI(hdc, pos[1].first, pos[1].second, 445*(hp[1] / 100.0f), 35, true);
}

void UIManager::UpdateHP(bool isLeft, int hp)
{
	this->hp[(int)isLeft] = hp;
}
