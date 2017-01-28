#include "TextBox.h"

TextBox::TextBox()
{
}

void TextBox::renderComment(SDL_Renderer* renderer)
{
	fontTexture.render(getX(), getY() + getHeight() / 4, renderer);
}

bool TextBox::loadText(SDL_Renderer* renderer, std::string text)
{
	//Loading success flag
	bool success = true;

	//Open the font
	fontTexture.setFont("lazy.ttf", 28);
	if (fontTexture.getFont() == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		int boxWidth = getWidth();
		if (!fontTexture.loadFromRenderedText(text, textColor, renderer, boxWidth))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	return success;
}

void TextBox::createStrings(std::string text)
{
	fontTexture.setFont("lazy.ttf", 28);
	if (fontTexture.getFont() == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		int tW, tH;
		TTF_SizeText(fontTexture.getFont(), "a", &tW, &tH);
		int maxCharsPerLine = getWidth() / tW;
		int numSubStrings = text.length() / maxCharsPerLine;

		std::vector<std::string> ret;

		std::stringstream threeChunks;
		int counter = 0;
		for (int i = 0; i < numSubStrings; i++)
		{
			std::string textChunk = text.substr(i * maxCharsPerLine, maxCharsPerLine);
			threeChunks << textChunk;
			counter++;
			if (counter == 3)
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

int TextBox::getLinesToRender()
{
	return textToRender.size();
}

std::string TextBox::returnLine(int i)
{
	return textToRender[i];
}

void TextBox::emptyTextToRender()
{
	textToRender.clear();
}

void TextBox::freeText()
{
	fontTexture.free();
}