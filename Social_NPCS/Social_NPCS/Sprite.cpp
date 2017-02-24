#include "Sprite.h"

Sprite::Sprite(){}

Sprite::Sprite(std::string fileName, SDL_Renderer* renderer, int x, int y): posX(x), posY(y), spriteFile(fileName)
{

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

void Sprite::setX(int x)
{
	posX = x;
}

void Sprite::setY(int y)
{
	posY = y;
}

void Sprite::render(SDL_Renderer* renderer)
{
	texture.render(posX, posY, renderer);
}

void Sprite::free()
{
	texture.free();
}

void Sprite::setColor(int r, int g, int b)
{
	texture.setColor(r, g, b);
}

bool Sprite::loadMedia(SDL_Renderer* renderer)
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if (!texture.loadFromFile(spriteFile, renderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}
	width = texture.getWidth();
	height = texture.getHeight();

	return success;
}