#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>

/**
* Implementation is based on the LTexture class from http://lazyfoo.net/tutorials/SDL/12_color_modulation/index.php it is a wrapper surrounding the SDL_Texture class
*/
class Texture
{
public:
	Texture();
	~Texture();
	///Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer* renderer);

	///Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* gFont, int wrapLength);

	///Deallocates texture
	void free();

	///Renders texture at given point
	void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	/// sets the sprites RBG values
	void setColor(int r, int g, int b);

	/// returns the SDL texture
	SDL_Texture* getSDLTexture();

	/// Gets image width
	int getWidth();

	/// Gets image height
	int getHeight();

private:
	///The actual hardware texture
	SDL_Texture* mTexture;

	///Image dimensions
	int mWidth;
	int mHeight;
};

