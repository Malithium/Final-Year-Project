#pragma once
#include "Texture.h"
#include <iostream>
class Sprite
{
public:
	Sprite();
	Sprite(std::string fileName, SDL_Renderer* renderer, int x = 0, int y = 0);

	int getWidth();
	int getHeight();

	int getX();
	int getY();

	void setY(int y);
	void setX(int x);

	void setColor(int r, int g, int b);
	void render(SDL_Renderer* renderer);
	void free();
	bool loadMedia(SDL_Renderer* renderer);
private:
	int posX, posY;
	int width, height;
	std::string spriteFile;

	Texture texture;
};

