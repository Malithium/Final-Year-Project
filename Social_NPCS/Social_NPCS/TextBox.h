#pragma once
#include "Sprite.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
/**
* Inherit's from the base sprite class, handles text rendering to the screen, and freeing up that text
*/
class TextBox : public Sprite
{
public:
	TextBox();
	TextBox(std::string fileName, SDL_Renderer* renderer, int x, int y);
	void renderComment(SDL_Renderer* renderer);
	bool loadText(SDL_Renderer* renderer, std::string text, TTF_Font* font);
	void createStrings(std::string text, TTF_Font* font);

	Texture getFontTexture();

	int getLinesToRender();

	void freeComment();

	std::string returnLine(int i);
	void emptyTextToRender();

private:
	int fontWidth, fontHeight;

	std::vector<std::string> textToRender;
	Texture fontTexture;
};

