#pragma once
#include "Sprite.h"
#include <vector>
#include <string>

class TextBox : public Sprite
{
public:
	TextBox();
	void renderComment(SDL_Renderer * renderer, int x, int y);
	bool loadText(SDL_Renderer* renderer, std::string text);
private:
	std::vector<std::string> textToRender;
	LoadTexture fontTexture;
};

