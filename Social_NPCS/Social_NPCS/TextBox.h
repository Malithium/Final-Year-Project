#pragma once
#include "Sprite.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

class TextBox : public Sprite
{
public:
	TextBox();
	void renderComment(SDL_Renderer * renderer);
	bool loadText(SDL_Renderer* renderer, std::string text);
	void createStrings(std::string text);

	int getLinesToRender();

	std::string returnLine(int i);
	void emptyTextToRender();

	void freeText();
private:
	std::vector<std::string> textToRender;
	LoadTexture fontTexture;
};

