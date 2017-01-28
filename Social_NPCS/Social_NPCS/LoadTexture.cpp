#include "LoadTexture.h"

LoadTexture::LoadTexture()
{
	texture = NULL;
	width = 0;
	height = 0;
}

LoadTexture::~LoadTexture()
{
	free();
}

bool LoadTexture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error : %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	texture = newTexture;
	return texture != NULL;
}

bool LoadTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, Uint32 nWidth)
{
	//Get rid of preexisting texture
	free();
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, textureText.c_str(), textColor, nWidth);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			width = textSurface->w;
			height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return texture != NULL;
}

void LoadTexture::free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void LoadTexture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, width, height };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

int LoadTexture::getWidth()
{
	return width;
}

int LoadTexture::getHeight()
{
	return height;
}

TTF_Font* LoadTexture::getFont()
{
	return font;
}

void LoadTexture::setFont(std::string file, int num)
{
	font = TTF_OpenFont(file.c_str(), num);
}