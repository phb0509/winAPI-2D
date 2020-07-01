#pragma once

class Program
{
public:
	static HDC backBuffer;

	Program();
	Program(HWND hWindow);
	~Program();

	void Update();
	void Render(HDC hdc);
private:
	//Scene* scene;	
	HBITMAP hBit;
};