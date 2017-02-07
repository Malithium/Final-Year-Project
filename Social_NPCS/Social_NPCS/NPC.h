#pragma once
#include "TextBox.h"
class NPC: public Sprite
{
public:
	NPC(std::string tBoxSprite, std::string NPCSprite, std::string text, SDL_Renderer* renderer, int x, int y);
	void prepareComment(std::string txt, TTF_Font* font);
	void LoadComment(SDL_Renderer* renderer, int i, TTF_Font* font);
	void LoadBox(SDL_Renderer* renderer);
	void renderBox(SDL_Renderer* renderer);
	void renderComment(SDL_Renderer* renderer);

	void freeBox();

	bool getSpeaking();
	void setSpeaking(bool val);

	bool getReadingTopic();
	void setReadingTopic(bool val);

	int getLinesToRender();
private:
	TextBox speech;
	bool speaking = false;
	bool readingTopic = false;
};

