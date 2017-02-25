#include "Texture.h"



Texture::Texture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}


Texture::~Texture()
{
	//Deallocate
	free();
}

bool Texture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
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
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* gFont, int wrapLength)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(gFont, textureText.c_str(), textColor, wrapLength);

	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != NULL;
}

void Texture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
}

void Texture::setColor(int r, int g, int b)
{
	SDL_SetTextureColorMod(mTexture, r, g, b);
}

void Texture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth()
{
	int w, h;
	SDL_QueryTexture(mTexture, NULL, NULL, &w, &h);
	return w;
}

int Texture::getHeight()
{
	int w, h;
	SDL_QueryTexture(mTexture, NULL, NULL, &w, &h);
	return h;
}