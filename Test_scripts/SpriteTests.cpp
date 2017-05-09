#include <gtest\gtest.h>
#include "Sprite.h"
#include "SDLWindow.h"

TEST(SpriteTest, TextureIsLoaded) {
	SDLWindow window("Social NPC's", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	Texture testTex;
	if (window.init())
	{
		Sprite sp1("NPC.png", window.getRenderer(), 10, 20);
		sp1.loadMedia(window.getRenderer());
		testTex = sp1.getTexture();
	}
	ASSERT_TRUE(testTex.getSDLTexture() != nullptr);
}