#include "NPC.h"

NPC::NPC(std::string tBoxSprite, std::string NPCSprite, std::string text, SDL_Renderer* renderer, int x, int y)
{
	setX(x);
	setY(y);
	loadMedia(renderer, NPCSprite);
	speech.loadMedia(renderer, tBoxSprite);
	speech.createStrings(text);
}

void NPC::prepareComment(std::string txt)
{
	speech.emptyTextToRender();
	speech.createStrings(txt);
}

void NPC::LoadComment(SDL_Renderer* renderer, int i)
{
	speech.freeText();
	std::string txt = speech.returnLine(i);
	speech.loadText(renderer, txt);
}

void NPC::LoadBox(SDL_Renderer* renderer)
{
	speech.loadMedia(renderer, "textbox.png");
}

void NPC::renderBox(SDL_Renderer* renderer)
{
	speech.setX(getX() - (speech.getWidth() / 4));
	speech.setY(getY() - ((getHeight()/4) + speech.getHeight()));
	speech.render(renderer);
}

void NPC::renderComment(SDL_Renderer* renderer)
{
	speech.renderComment(renderer);
}

int NPC::getLinesToRender()
{
	return speech.getLinesToRender();
}

void NPC::freeComment()
{
	speech.freeText();
	speech.free();
}

bool NPC::getSpeaking()
{
	return speaking;
}

void NPC::setSpeaking(bool val)
{
	speaking = val;
}