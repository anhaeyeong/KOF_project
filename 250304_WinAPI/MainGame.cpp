#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "KOF_Iori.h"
#include "Character.h"
#include "Ryo.h"
#include "Mai.h"
#include "Clark.h"


/*
	�ǽ�1. �̿��� ���� ������
	�ǽ�2. ��� �ٲٱ� (ŷ���� �ִϸ��̼� ���)
*/

void MainGame::Init()
{
	UIManager::GetInstance()->Init();
	
	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd, 
			TEXT("����� ���� ����"), TEXT("���"), MB_OK);
	}
	backGround = new Image();
	if (FAILED(backGround->Init(TEXT("Image/kof_animBackground.bmp"),768, 8784, 1, 36)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/kof_animBackground.bmp ���� ����"), TEXT("���"), MB_OK);
	}


	mai = new Mai();
	mai->Init();

	ryo = new Ryo();
	ryo->Init();

	CollisionManager::GetInstance()->Init(ryo, mai);
}

void MainGame::Release()
{
	if (mai)
	{
		mai->Release();
		delete mai;
		mai = nullptr;
	}

	if (ryo)
	{
		ryo->Release();
		delete ryo;
		ryo = nullptr;
	}

	if (backGround)
	{
		backGround->Release();
		delete backGround;
		backGround = nullptr;
	}

	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}
}

void MainGame::Update()
{
	if (mai)
	{
		mai->Update();
		// mai�� ������ null�� �о��ְ� clark ����
		if (mai->GetState() == State::DEAD && mai->GetAnimationFrame() == 10)
		{
			mai->Release();
			delete mai;
			mai = nullptr;
			clark = new Clark();
			clark->Init();
			clark->SetHP(100);
			CollisionManager::GetInstance()->set(clark, false);
		}
	}
	if (clark)
	{
		clark->Update();
		if (clark->GetState() == State::DEAD)
		{
			clark->Release();
			delete clark;
			clark = nullptr;
		}
	}
	if (ryo)
	{
		ryo->Update();
	}
	backGroundFrame++;
	if (backGroundFrame >= 36)	backGroundFrame = 0;

	
		


	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	// ����ۿ� ���� ����
	HDC hBackBufferDC = backBuffer->GetMemDC();

	backGround->RenderBackGround(hBackBufferDC, backGroundFrame);
	if (mai) mai->Render(hBackBufferDC);
	if (ryo)
	{
		ryo->Render(hBackBufferDC);
	}
	if (clark) clark->Render(hBackBufferDC);

	UIManager::GetInstance()->Render(hBackBufferDC);

	// ����ۿ� �ִ� ������ ���� hdc�� ����
	backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd, 0, 100, NULL);

		break;
	case WM_TIMER:
		this->Update();
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'a': case 'A':
			break;
		case 'd': case 'D':
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		mousePos.x = LOWORD(lParam);
		mousePos.y = HIWORD(lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);

		this->Render(hdc);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}
