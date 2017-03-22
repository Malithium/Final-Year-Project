#include "NPC.h"

NPC::NPC(std::string tBoxSprite, std::string NPCSprite, std::string text, SDL_Renderer* renderer, int x, int y) : Sprite(NPCSprite, renderer, x, y)
{
	boredLvl = 0;
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

void NPC::setID(int i)
{
	id = i;
}

int NPC::getID()
{
	return id;
}

void NPC::setGroupID(int id)
{
	groupID = id;
}

int NPC::getGroupID()
{
	return groupID;
}

int NPC::getBoredom()
{
	return boredLvl;
}

void NPC::move()
{
	if (path.size() > 0)
	{
		float movementX = path[0]->getX() - getX();
		float movementY = path[0]->getY() - getY();

		float toWayPointLength = sqrt(movementX*movementX + movementY*movementY);
		if (toWayPointLength > 0)
		{
			movementX = movementX / toWayPointLength;
			movementY = movementY / toWayPointLength;
		}

		float nX = getX();
		float nY = getY();
		setX(nX += movementX * 2);
		setY(nY += movementY * 2);

		if (path[0]->getX() - getX() < 3 && path[0]->getY() - getY() < 3 && path[0]->getX() - getX() > -3 && path[0]->getY() - getY() > -3)
		{
			setX(path[0]->getX());
			setY(path[0]->getY());
			path.erase(path.begin());
		}
	}
}

void NPC::setBoredom(int lvl)
{
	boredLvl = lvl;
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
int NPC::getCurrentLine()
{
	return currentLine;
}

void NPC::setCurrentLine(int line)
{
	currentLine = line;
}

void NPC::setSpeaking(bool val)
{
	speaking = val;
}

void NPC::applyEmotionLevel(float val)
{
	emotionLevels += val;
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

std::vector<std::shared_ptr<Node>> NPC::getPath()
{
	return path;
}

void NPC::setPath(std::vector<std::shared_ptr<Node>> newPath)
{
	path = newPath;
}
bool NPC::getReading()
{
	return reading;
}

void NPC::setReading(bool read)
{
	reading = read;
}

bool NPC::getMoving()
{
	return moving;
}
void NPC::setMoving(bool move)
{
	moving = move;
}

bool operator== (const NPC &c1, const NPC &c2)
{
	return (c1.id == c2.id);
}