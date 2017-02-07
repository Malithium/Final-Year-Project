#include "NPC.h"

NPC::NPC(std::string tBoxSprite, std::string NPCSprite, std::string text, SDL_Renderer* renderer, int x, int y) : Sprite(NPCSprite, renderer, x, y)
{
	speech = TextBox(tBoxSprite, renderer, x, y);
}

void NPC::prepareComment(std::string txt, TTF_Font* font)
{
	speech.emptyTextToRender();
	speech.createStrings(txt, font);
}

void NPC::LoadComment(SDL_Renderer* renderer, int i, TTF_Font* font)
{
	std::string txt = speech.returnLine(i);
	speech.loadText(renderer, txt, font);
}

void NPC::LoadBox(SDL_Renderer* renderer)
{
	speech.setX(getX() - 40);
	speech.setY(getY() - 120);
	speech.loadMedia(renderer);
}

void NPC::renderBox(SDL_Renderer* renderer)
{
	speech.render(renderer);
}

void NPC::freeBox()
{
	speech.free();
	speech.freeComment();
}

void NPC::renderComment(SDL_Renderer* renderer)
{
	speech.renderComment(renderer);
}

int NPC::getLinesToRender()
{
	return speech.getLinesToRender();
}

bool NPC::getSpeaking()
{
	return speaking;
}

void NPC::setSpeaking(bool val)
{
	speaking = val;
}

bool NPC::getReadingTopic()
{
	return readingTopic;
}

void NPC::setReadingTopic(bool val)
{
	readingTopic = val;
}