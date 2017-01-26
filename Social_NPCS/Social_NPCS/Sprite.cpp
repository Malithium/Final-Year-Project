#include "Sprite.h"

Sprite::Sprite(int x, int y, LoadTexture l)
{
	posX = x;
	posY = y;
	loader = l;
}

int Sprite::getHeight()
{
	return height;
}

int Sprite::getWidth()
{
	return width;
}

int Sprite::getX()
{
	return posX;
}

int Sprite::getY()
{
	return posY;
}

void Sprite::render(SDL_Renderer* renderer)
{
	loader.render(posX, posY, renderer);
}

bool Sprite::loadMedia(SDL_Renderer* renderer, std::string file)
{
	bool success = true;

	if (!loader.loadFromFile(file, renderer))
	{
		printf("Failed to load the media!\n");
		success = false;
	}
	width = loader.getWidth();
	height = loader.getHeight();

	return success;
}