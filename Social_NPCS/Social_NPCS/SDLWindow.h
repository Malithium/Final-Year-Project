#pragma once
#include <SDL.h>
#include <string>
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
private:
	SDL_Window* Window;
	SDL_Surface* Surface;

	const char* SCREEN_TITLE;
	int SCREEN_X;
	int SCREEN_Y;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	Uint32 SCREEN_FLAG;
};

