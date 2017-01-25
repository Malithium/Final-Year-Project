#include "SDLWindow.h"



SDLWindow::SDLWindow(char* title, int x, int y, int width, int height, Uint32 flag): SCREEN_X(x), SCREEN_Y(y), SCREEN_WIDTH(width), SCREEN_HEIGHT(height), SCREEN_TITLE(title), SCREEN_FLAG(flag)
{
	
}

SDLWindow::~SDLWindow()
{
	SDL_FreeSurface(Surface);
	Surface = NULL;
	SDL_DestroyWindow(Window);
	Window = NULL;
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
		setWindow(SCREEN_TITLE, SCREEN_X, SCREEN_Y, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_FLAG);
		if (Window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			Surface = SDL_GetWindowSurface(Window);
		}
	}

	return success;
}