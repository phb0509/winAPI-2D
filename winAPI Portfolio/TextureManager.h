#pragma once

class TextureManager
{
private:
	TextureManager();
	~TextureManager();

public:
	static TextureManager* Get()
	{
		//if (instance == nullptr)
			//instance = new TextureManager();
		//static TextureManager instance;
		return instance;
	}

	static void Create()
	{
		instance = new TextureManager();
	}
	static void Delete()
	{
		delete instance;
	}

	Texture* BitmapAdd(wstring path, int width, int height,
		COLORREF transColor = MAGENTA);
	Texture* BitmapAdd(wstring path, int width, int height,
		int frameX, int frameY, COLORREF transColor = MAGENTA);

	

	bool isDebug;
private:
	static TextureManager* instance;

	map<wstring, Texture*> textures;

	Gdiplus::GdiplusStartupInput input;
	ULONG_PTR token;
};