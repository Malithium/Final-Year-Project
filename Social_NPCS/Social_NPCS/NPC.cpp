#include "NPC.h"

NPC::NPC(std::string tBoxSprite, std::string NPCSprite, std::string text, SDL_Renderer* renderer, int x, int y) : Sprite(NPCSprite, renderer, x, y)
{
	boredLvl = 0;
	speech = TextBox(tBoxSprite, renderer, x, y);
}

/**
* Break up the parsed in text into chunks to be scrolled
*/
void NPC::prepareComment(std::string txt, TTF_Font* font)
{
	speech.emptyTextToRender();
	speech.createStrings(txt, font);
}

/**
* Load in a comment as a texture
*/
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

std::string NPC::getCurrentUser()
{
	return currentUser;
}

void NPC::setCurrentUser(std::string user)
{
	currentUser = user;
}

/**
* The NPCs movement method
*/
void NPC::move()
{
	// if there is a path that the NPC can follow
	if (path.size() > 0)
	{
		// Deduct the NPCs X & Y from the path nodes X & Y
		float movementX = path[0]->getX() - getX();
		float movementY = path[0]->getY() - getY();

		// Find the length between the NPC and the node
		float toWayPointLength = sqrt(movementX*movementX + movementY*movementY);
		
		// If the node has not been reached, then divide the movement values by the length
		if (toWayPointLength > 0)
		{
			movementX = movementX / toWayPointLength;
			movementY = movementY / toWayPointLength;
		}

		float nX = getX();
		float nY = getY();

		// apply the movements value multiplied by a speed of 2
		setX(nX += movementX * 2);
		setY(nY += movementY * 2);

		// If the NPC is close to the node, set him to occupy that node space
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

/**
* Load the Textbox into memory
*/
void NPC::LoadBox(SDL_Renderer* renderer)
{
	speech.setX(getX() - 40);
	speech.setY(getY() - 120);
	speech.loadMedia(renderer);
}


/**
* Render the textbox to the screen
*/
void NPC::renderBox(SDL_Renderer* renderer)
{
	speech.render(renderer);
}

/**
* Frees the space that both the comment and its textbox occupy in memory
*/
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

/**
* Evaluates the NPCs emotion level and converts it into RGB values
*/
void NPC::evaluateEmotionLevel()
{
	int emo = getEmotionLevel();

	// if the emotion level is less than 0 it is negative
	if (emo < 0)
	{
		emo = abs(emo) * 10;

		// ensure that the highest possible value is 255
		if (emo > 255)
			emo = 255;

		// set the NPCs color to be more red to show negativity
		setColor(255, 255-emo, 255-emo);
	}
	else if(emo > 0)
	{

		emo = emo * 10;

		if (emo > 255)
			emo = 255;

		// set the NPCs color to be more green to show positivity
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