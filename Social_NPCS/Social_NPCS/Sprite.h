#pragma once
#include "LoadTexture.h"
class Sprite
{
public:
	Sprite( int x = 0, int y = 0, LoadTexture l = LoadTexture());

	int getWidth();
	int getHeight();

	int getX();
	int getY();

	virtual void render(SDL_Renderer* renderer);
	bool loadMedia(SDL_Renderer* renderer, std::string file);
private:
	int posX, posY;
	int width, height;

	LoadTexture loader;
};

