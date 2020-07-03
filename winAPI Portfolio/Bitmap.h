#pragma once

class Bitmap : public Texture
{
public:
	Bitmap(wstring file, int width, int height, COLORREF transColor = MAGENTA);
	Bitmap(wstring file, int width, int height,
		int frameX, int frameY, COLORREF transColor = MAGENTA);
	~Bitmap();

	void CreateBitmap(wstring file, int width, int height);

	void Render(Rect* rect) override;
	void Render(Rect* rect, POINT curFrame) override;

	HDC GetMemDC() { return memDC; }
private:
	HDC memDC;
	HBITMAP bitmap;

	COLORREF transColor;


	BLENDFUNCTION blendFunc;
};