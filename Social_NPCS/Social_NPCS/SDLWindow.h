#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
/**
* wrapper for the SDL window and renderer within the application
*/
class SDLWindow
{
public:
	SDLWindow(char* title, int x, int y, int width, int height, Uint32 flag);
	~SDLWindow();

	bool init();

	int getScreenWidth();
	void setScreenWidth(int width);

	int getScreenHeight();
	void setScreenHeight(int height);

	const char* getScreenTitle();
	void setScreenTitle(const char* title);

	Uint32 getScreenFlag();
	void setScreenFlag(Uint32 flag);

	SDL_Window* getWindow();
	void setWindow(const char* title, int x, int y, int width, int height, Uint32 flag);

	SDL_Renderer* getRenderer();
private:
	SDL_Window* Window;
	SDL_Surface* Surface;
	SDL_Renderer* Renderer;

	const char* SCREEN_TITLE;
	int SCREEN_X;
	int SCREEN_Y;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	Uint32 SCREEN_FLAG;
};

