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

float NPC::getEmotionLevel()
{
	return emotionLevels;
}

void NPC::evaluateEmotionLevel()
{
	int emo = getEmotionLevel();

	if (emo < 0)
	{
		emo = abs(emo) * 10;
		if (emo > 255)
			emo = 255;
		setColor(255, 255-emo, 255-emo);
	}
	else if(emo > 0)
	{
		emo = emo * 10;
		if (emo > 255)
			emo = 255;
		setColor(255-emo, 255, 255-emo);
	}
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

void NPC::applyEmotionLevel(float val)
{
	emotionLevels += val;
}

void NPC::setBoredom(int bored)
{
	boredom = bored;
}

int NPC::getBoredom()
{
	return boredom;
}

void NPC::setText(std::string str)
{
	text = str;
}

std::string NPC::getText()
{
	return text;
}

bool NPC::getIdle()
{
	return idle;
}

void NPC::setIdle(bool nIdle)
{
	idle = nIdle;
}

std::pair<int, int> NPC::getEndGoal()
{
	return endGoal;
}

void NPC::setEndGoal(std::pair<int, int> newGoal)
{
	endGoal = newGoal;
}

SDL_Rect NPC::getBBox()
{
	return colliderBox;
}

void NPC::setBBox(int x, int y, int w, int h)
{
	colliderBox.x = x;
	colliderBox.y = y;
	colliderBox.w = w;
	colliderBox.h = h;

}

std::vector<std::shared_ptr<Node>> NPC::getPath()
{
	return path;
}

void NPC::setPath(std::vector<std::shared_ptr<Node>> newPath)
{
	path = newPath;
}