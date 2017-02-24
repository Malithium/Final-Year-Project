#include "TextBox.h"

TextBox::TextBox(){}

TextBox::TextBox(std::string fileName, SDL_Renderer* renderer, int x, int y): Sprite(fileName, renderer, x, y){}

void TextBox::renderComment(SDL_Renderer* renderer)
{
	fontTexture.render(getX(), getY(), renderer);
}

bool TextBox::loadText(SDL_Renderer* renderer, std::string text, TTF_Font* font)
{
	//Loading success flag
	bool success = true;

	//Open the font
	if (font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (!fontTexture.loadFromRenderedText(text, textColor, renderer, font, getWidth()))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
		fontWidth = fontTexture.getWidth();
		fontHeight = fontTexture.getHeight();
	}

	return success;
}

void TextBox::createStrings(std::string text, TTF_Font* font)
{
	if (font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		int tW, tH;
		TTF_SizeText(font, "a", &tW, &tH);
		int supposedWidth = getWidth();
		int maxCharsPerLine = supposedWidth / tW;
		int numSubStrings = text.length() / maxCharsPerLine;
		std::vector<std::string> ret;

		std::stringstream threeChunks;
		int counter = 0;
		for (int i = 0; i < numSubStrings; i++)
		{
			std::string textChunk = text.substr(i * maxCharsPerLine, maxCharsPerLine);
			threeChunks << textChunk;
			counter++;
			if (counter == 3 || counter == numSubStrings)
			{
				counter = 0;
				textToRender.push_back(threeChunks.str());
				threeChunks.str("");
			}
		}

		if (text.length() % maxCharsPerLine != 0)
		{
			threeChunks << text.substr(maxCharsPerLine * numSubStrings);
			textToRender.push_back(threeChunks.str());
			threeChunks.str("");
		}
	}
}

void TextBox::freeComment()
{
	fontTexture.free();
}

int TextBox::getLinesToRender()
{
	return textToRender.size();
}

std::string TextBox::returnLine(int i)
{
	if (textToRender.size() > 0)
		return textToRender[i];
	else
		return "";
}

void TextBox::emptyTextToRender()
{
	textToRender.clear();
}