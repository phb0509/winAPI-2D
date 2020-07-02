#include "Framework.h"
#include "TextureManager.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager()
{
	Gdiplus::GdiplusStartup(&token, &input, nullptr);
}

TextureManager::~TextureManager()
{
	for (auto texture : textures)
		delete texture.second;

	textures.clear();

	Gdiplus::GdiplusShutdown(token);
}

Texture* TextureManager::BitmapAdd(wstring path, int width, int height, COLORREF transColor)
{
	if (textures.count(path) > 0)
		return textures[path];

	Texture* texture = new Bitmap(path, width, height, transColor);
	textures[path] = texture;

	return texture;
}

