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

Texture* TextureManager::BitmapAdd(wstring path, int width, int height, int frameX, int frameY, COLORREF transColor)
{
	if (textures.count(path) > 0)
		return textures[path];

	Texture* texture = new Bitmap(path, width, height, frameX, frameY, transColor);
	textures[path] = texture;

	return texture;
}

Texture* TextureManager::PlusmapAdd(wstring path, Gdiplus::Color transColor)
{
	if (textures.count(path) > 0)
		return textures[path];

	Texture* texture = new Plusmap(path, transColor);
	textures[path] = texture;

	return texture;
}

Texture* TextureManager::PlusmapAdd(wstring path, int frameX, int frameY, Gdiplus::Color transColor)
{
	if (textures.count(path) > 0)
		return textures[path];

	Texture* texture = new Plusmap(path, frameX, frameY, transColor);
	textures[path] = texture;

	return texture;
}