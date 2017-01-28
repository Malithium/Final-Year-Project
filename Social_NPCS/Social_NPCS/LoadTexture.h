#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
class LoadTexture
{
public:
	LoadTexture();
	~LoadTexture();

	bool loadFromFile(std::string path, SDL_Renderer* renderer);

	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, Uint32 nWidth);

	void free();

	void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth();
	int getHeight();

	TTF_Font* getFont();
	void setFont(std::string path, int num);
private:
	SDL_Texture* texture;
	TTF_Font* font;

	int width;
	int height;
};

