#pragma once

class Texture
{
public:
	Texture();
	virtual ~Texture();

	virtual void Render(Rect* rect) {}
	virtual void Render(Rect* rect, POINT curFrame) {}
	virtual void Render(Rect* rect, RECT rectFrame) {}

	virtual void AlphaRender(Rect* rect, int alpha) {}
	virtual void AlphaRender(Rect* rect, POINT curFrame, int alpha) {}

	virtual HDC GetMemDC() { return nullptr; }

	void UpdateBorderLine(Rect* rect);
	void DrawBorderLine(Rect* rect);

	POINT OriginSize() { return originSize; }
	POINT FrameSize() { return frameSize; }
	POINT MaxFrame() { return maxFrame; }

	Vector2 Size() { return Vector2((double)frameSize.x, (double)frameSize.y); }

protected:
	POINT originSize;
	POINT frameSize;
	POINT maxFrame;

	Line borderLine[4];
	HPEN borderPen;
};