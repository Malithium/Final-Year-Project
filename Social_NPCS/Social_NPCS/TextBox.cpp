#include "TextBox.h"

TextBox::TextBox(){}

TextBox::TextBox(std::string fileName, SDL_Renderer* renderer, int x, int y): Sprite(fileName, renderer, x, y){}

void TextBox::renderComment(SDL_Renderer* renderer)
{
	fontTexture.render(getX(), getY(), renderer);
}

Texture TextBox::getFontTexture()
{
	return fontTexture;
}

/**
* Load parsed in text as a texture
*/
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

/**
* Breaks up text into 3 line chunks to be rendered
*/
void TextBox::createStrings(std::string text, TTF_Font* font)
{
	if (font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		try
		{
			// Find the dimensions of a single character rendered in the parsed in font
			int tW, tH;
			TTF_SizeText(font, "a", &tW, &tH);

			// retrieve the width of our texture
			int supposedWidth = getWidth();
			
			/** @bug There is currently an issue where the texture will return 0, temp fix has been implemented where the texture width is hardcoded */
			int maxCharsPerLine = 180 / tW;

			if (maxCharsPerLine == 0)
				throw std::overflow_error("texture Width is 0!");
			
			// Divide the length of text by the max number of chars that can be had per line
			int numSubStrings = text.length() / maxCharsPerLine;
			std::vector<std::string> ret;


			std::stringstream threeChunks;
			int counter = 0;
			for (int i = 0; i < numSubStrings; i++)
			{
				// Create a substring using the maxCharPerLine value 
				std::string textChunk = text.substr(i * maxCharsPerLine, maxCharsPerLine);

				// feed the chunk into our string stream
				threeChunks << textChunk;
				counter++;

				// if we have 3 lines stored, push back the chunk
				if (counter == 3 || counter == numSubStrings)
				{
					counter = 0;
					textToRender.push_back(threeChunks.str());
					threeChunks.str("");
				}
			}

			// add the remainder text as a chunk
			if (text.length() % maxCharsPerLine != 0)
			{
				threeChunks << text.substr(maxCharsPerLine * numSubStrings);
				textToRender.push_back(threeChunks.str());
				threeChunks.str("");
			}
		}
		catch (std::overflow_error e)
		{
			std::cout << e.what() << std::endl;;
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