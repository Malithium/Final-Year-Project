#include "TextBox.h"

TextBox::TextBox()
{
}

void TextBox::renderComment(SDL_Renderer* renderer, int x, int y)
{
	fontTexture.render(x, y, renderer);
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
		if (!fontTexture.loadFromRenderedText(text, textColor, renderer))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	return success;
}