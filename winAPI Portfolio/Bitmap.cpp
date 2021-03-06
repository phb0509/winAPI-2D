#include "Framework.h"

Bitmap::Bitmap(wstring file, int width, int height, COLORREF transColor)
	: transColor(transColor)
{
	CreateBitmap(file, width, height);

	frameSize = { width, height };
	maxFrame = { 1, 1 };
}

Bitmap::Bitmap(wstring file, int width, int height, int frameX, int frameY, COLORREF transColor)
	: transColor(transColor)
{
	CreateBitmap(file, width, height);

	frameSize = { width / frameX, height / frameY };
	maxFrame = { frameX, frameY };
}

Bitmap::~Bitmap()
{
	DeleteDC(memDC);
	DeleteObject(bitmap);

}

void Bitmap::CreateBitmap(wstring file, int width, int height)
{
	HDC hdc = GetDC(hWnd);
	memDC = CreateCompatibleDC(hdc);
	ReleaseDC(hWnd, hdc);
	bitmap = (HBITMAP)LoadImage(hInst, file.c_str(), IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);

	SelectObject(memDC, bitmap);

	originSize = { width, height };
}

void Bitmap::Render(Rect* rect)
{
	GdiTransparentBlt(Program::backBuffer,
		(int)(rect->Left()),
		(int)(rect->Top()),
		(int)(rect->size.x),
		(int)(rect->size.y),
		memDC,
		0, 0,
		frameSize.x, frameSize.y,
		transColor
	);

	DrawBorderLine(rect);

}

void Bitmap::Render(Rect* rect, POINT curFrame)
{
	GdiTransparentBlt(Program::backBuffer,
		(int)(rect->Left()),
		(int)(rect->Top()),
		(int)(rect->size.x),
		(int)(rect->size.y),
		memDC,
		frameSize.x * curFrame.x, frameSize.y * curFrame.y,
		frameSize.x, frameSize.y,
		transColor
	);

	DrawBorderLine(rect);
}

