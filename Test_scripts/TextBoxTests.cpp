#include <gtest\gtest.h>
#include "TextBox.h"
#include "SDLWindow.h"

TEST(TextBoxTest, SpriteTextureIsLoaded) {
	SDLWindow window("Social NPC's", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	Texture testTex;
	if (window.init())
	{
		TextBox txt1("TextBox.png", window.getRenderer(), 10, 20);
		txt1.loadMedia(window.getRenderer());
		testTex = txt1.getTexture();
	}
	ASSERT_TRUE(testTex.getSDLTexture() != nullptr);
}

TEST(TextBoxTest, FontTextureIsLoaded)
{
	TTF_Font* font;
	font = TTF_OpenFont("lazy.ttf", 11);
	SDLWindow window("Social NPC's", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	window.init();
	TextBox txt1("TextBox.png", window.getRenderer(), 10, 20);
	txt1.loadMedia(window.getRenderer());
	txt1.loadText(window.getRenderer(), "Test text for the win", font);
	ASSERT_TRUE(txt1.getFontTexture().getSDLTexture() != nullptr);
}

TEST(TextBoxTest, SmallTextIsLessThanSpriteWidth)
{
	TTF_Font* font;
	font = TTF_OpenFont("lazy.ttf", 11);
	SDLWindow window("Social NPC's", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	window.init();
	TextBox txt1("TextBox.png", window.getRenderer(), 10, 20);
	txt1.loadMedia(window.getRenderer());
	txt1.loadText(window.getRenderer(), "Test text for the win", font);
	ASSERT_TRUE(txt1.getFontTexture().getWidth() < txt1.getTexture().getWidth());
}

TEST(TextBoxTest, LargeTextIsEqualToSpriteWidth)
{
	TTF_Font* font;
	font = TTF_OpenFont("lazy.ttf", 11);
	SDLWindow window("Social NPC's", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	window.init();
	TextBox txt1("TextBox.png", window.getRenderer(), 10, 20);
	txt1.loadMedia(window.getRenderer());
	txt1.loadText(window.getRenderer(), "Test text for the win, this is more text to pad out the width of the texture", font);
	ASSERT_TRUE(txt1.getFontTexture().getWidth() == txt1.getTexture().getWidth());
}

TEST(TextBoxTest, LargeTextMovesOntoNewLines)
{
	TTF_Font* font;
	font = TTF_OpenFont("lazy.ttf", 11);
	SDLWindow window("Social NPC's", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	window.init();
	TextBox txt1("TextBox.png", window.getRenderer(), 10, 20);
	txt1.loadMedia(window.getRenderer());
	txt1.createStrings("Test text for the win, this is more text to pad out the width of the texture", font);

	ASSERT_TRUE(txt1.getLinesToRender() > 1);
}