#include "SDLWindow.h"

SDLWindow::SDLWindow()
{

}

SDLWindow::SDLWindow(char* title, int x, int y, int width, int height, Uint32 flag): SCREEN_X(x), SCREEN_Y(y), SCREEN_WIDTH(width), SCREEN_HEIGHT(height), SCREEN_TITLE(title), SCREEN_FLAG(flag)
{

}

SDLWindow::~SDLWindow()
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	Window = NULL;
	Renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}

void SDLWindow::setWindow(const char* title, int x, int y, int width, int height, Uint32 flag)
{
	Window = SDL_CreateWindow(title, x, y, width, height, flag);
}

SDL_Window* SDLWindow::getWindow()
{
	return Window;
}

int SDLWindow::getScreenHeight()
{
	return SCREEN_HEIGHT;
}

void SDLWindow::setScreenHeight(int height)
{
	SCREEN_HEIGHT = height;
}

int SDLWindow::getScreenWidth()
{
	return SCREEN_WIDTH;
}

void SDLWindow::setScreenWidth(int width)
{
	SCREEN_WIDTH = width;
}

const char* SDLWindow::getScreenTitle()
{
	return SCREEN_TITLE;
}

void SDLWindow::setScreenTitle(const char* title)
{
	SCREEN_TITLE = title;
}

Uint32 SDLWindow::getScreenFlag()
{
	return SCREEN_FLAG;
}

void SDLWindow::setScreenFlag(Uint32 flag)
{
	SCREEN_FLAG = flag;
}

SDL_Renderer* SDLWindow::getRenderer()
{
	return Renderer;
}

bool SDLWindow::init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		setWindow(SCREEN_TITLE, SCREEN_X, SCREEN_Y, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_FLAG);
		if (Window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (Renderer == NULL)
			{
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}