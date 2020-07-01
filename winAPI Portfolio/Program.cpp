#include "Framework.h"


HDC Program::backBuffer = nullptr;

Program::Program()
{
	//scene = new PaintScene();	
	//scene = new CollisionScene();
}

Program::Program(HWND hWindow)
{
	//Timer::Get()->SetLockFPS(60);

	srand((unsigned)time(nullptr));
	hWnd = hWindow;

	HDC hdc = GetDC(hWnd);

	backBuffer = CreateCompatibleDC(hdc);
	hBit = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
	SelectObject(backBuffer, hBit);

	SetBkMode(backBuffer, TRANSPARENT);

	ReleaseDC(hWnd, hdc);

	/*SCENE->Add("start", new AlphaScene());

	SCENE->ChangeScene("start");*/
}

Program::~Program()
{
	//delete scene;

	DeleteObject(hBit);
	DeleteDC(backBuffer);
}

void Program::Update()
{
	Keyboard::Get()->Update();
	Timer::Get()->Update();
	//FXManager::Get()->Update();
	//SoundManager::Get()->Update();
	//CAM->Update();

	if (KEYDOWN(VK_F1))
	{
		TEX->isDebug = !TEX->isDebug;
	}

	SCENE->Update();
	//scene->Update();

	InvalidateRect(hWnd, nullptr, false);
}

void Program::Render(HDC hdc)
{
	PatBlt(backBuffer, 0, 0, WIN_WIDTH, WIN_HEIGHT, WHITENESS);

	//scene->Render(backBuffer);
	SCENE->Render(backBuffer);
	//FXManager::Get()->Render();

	Timer::Get()->Render();

	BitBlt(
		//목적지
		hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT,
		//복사할 정보
		backBuffer, 0, 0, SRCCOPY
	);
}
