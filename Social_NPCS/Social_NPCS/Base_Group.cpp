#include "Base_Group.h"



Base_Group::Base_Group()
{
}

/*
The NPC_Group class is designed to represent a maximum group of 6 NPC's.
the specfied NPC's are initialised when the group is initialised.
*/
Base_Group::Base_Group(int x, int y, int size, std::string tBoxFile, std::string npcFile, SDL_Renderer* renderer, Topic tp) : GroupX(x), GroupY(y), GroupSize(size)
{
	script = tp.getComments();
	topicString = tp.getTopic();
	availableSpace.push_back(std::pair<int, int>(GroupX, GroupY - 35));
	availableSpace.push_back(std::pair<int, int>(GroupX + 35, GroupY - 17));
	availableSpace.push_back(std::pair<int, int>(GroupX + 35, GroupY + 17));
	availableSpace.push_back(std::pair<int, int>(GroupX, GroupY + 35));
	availableSpace.push_back(std::pair<int, int>(GroupX - 35, GroupY + 17));
	availableSpace.push_back(std::pair<int, int>(GroupX - 35, GroupY - 17));
}

bool Base_Group::isAvailable()
{
	if (availableSpace.size() > 0)
		return true;
	else
		return false;
}

std::pair<int, int> Base_Group::getSpace()
{
	if (isAvailable()) {
		std::pair<int, int> recoveredSpace = availableSpace[0];
		return recoveredSpace;
	}
}

bool Base_Group::joinSpace(std::shared_ptr<NPC> npc)
{
	bool success = false;
	if (NPCs.size() < 6)
	{
		if (isAvailable())
		{
			std::pair<int, int> newPos = getSpace();
			availableSpace.erase(std::remove(availableSpace.begin(), availableSpace.end(), availableSpace[0]), availableSpace.end());
			npc->setEndGoal(newPos);
			if (NPCs.size() == 0)
			{
				npc->setSpeaking(true);
			}
			npc->setGroupID(ID);
			NPCs.push_back(npc);
			success = true;
		}
		else
			return success;
	}
	else
	{
		return success;
	}

	return success;
}

int Base_Group::getID()
{
	return ID;
}

void Base_Group::setID(int id)
{
	ID = id;
}

void Base_Group::leaveSpace(std::shared_ptr<NPC> npc)
{
	for (int i = 0; i < NPCs.size(); i++)
	{
		if (NPCs[i]->getID() == npc->getID())
		{
			availableSpace.push_back(std::pair<int, int>(npc->getX(), npc->getY()));
			NPCs.erase(std::remove(NPCs.begin(), NPCs.end(), npc), NPCs.end());
		}
	}
}

bool Base_Group::AddToGroup(std::shared_ptr<NPC> nNPC)
{
	bool success = false;
	if (NPCs.size() < 6)
	{
		if (isAvailable())
		{
			std::pair<int, int> newPos = getSpace();
			nNPC->setEndGoal(newPos);
			nNPC->setX(newPos.first);
			nNPC->setY(newPos.second);
			availableSpace.erase(std::remove(availableSpace.begin(), availableSpace.end(), availableSpace[0]), availableSpace.end());
			if (NPCs.size() == 0)
			{
				nNPC->setSpeaking(true);
			}
			NPCs.push_back(nNPC);
			success = true;
		}
		else
			return success;
	}
	else
	{
		return success;
	}

	return success;
}

std::vector<Comment> Base_Group::getScript()
{
	return script;
}

/*
returns the NPCs in the group
*/
std::vector<std::shared_ptr<NPC>> Base_Group::getNPCList()
{
	return NPCs;
}

int Base_Group::getLastSpoken()
{
	return lastSpoken;
}

void Base_Group::setLastSpoken(int spoke)
{
	lastSpoken = spoke;
}

bool Base_Group::getIsReply()
{
	return isReply;
}

void Base_Group::setIsReply(bool reply)
{
	isReply = reply;
}

float Base_Group::getPolar()
{
	return polar;
}

void Base_Group::setPolar(float pol)
{
	polar = pol;
}

/*
a method that handles the background logic of the NPC conversation's within the group.
*/
int Base_Group::GetRandomNumber()
{
	if (NPCs.size() > 0)
	{
		int gSize = NPCs.size();

		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> distGroup(0, gSize - 1);

		int random = distGroup(rng);
		//if the random number matches our current NPC, change its value
		if (random == lastSpoken)
		{
			if (random == NPCs.size() - 1)
				random--;
			else
				random++;
		}

		if (random < 0)
			random = NPCs.size() - 1;

		if (NPCs[random]->getIdle() == true)
		{
			random--;
			if (random == lastSpoken)
				random + 2;
		}

		if (random < 0)
			random = NPCs.size() - 1;

		return random;
	}
	return 0;
}
/*
renders the textbox and comments of the NPC's
*/
void Base_Group::renderConversation(SDL_Renderer* renderer)
{
	std::vector<std::shared_ptr<NPC>>::iterator npcIterator;
	for (npcIterator = NPCs.begin(); npcIterator != NPCs.end(); npcIterator++)
	{
		//render the comment of the NPC currently speaking
		if ((*npcIterator)->getSpeaking()) {
			(*npcIterator)->renderBox(renderer);
			(*npcIterator)->renderComment(renderer);
		}
	}
}

void Base_Group::cleanUpGroup()
{
	for (int i = 0; i < NPCs.size(); i++)
	{
		NPCs[i]->setIdle(true);
		NPCs[i]->setSpeaking(false);
		NPCs[i]->setReading(false);
		NPCs[i]->setText("");
		NPCs[i]->setGroupID(-1);
		leaveSpace(NPCs[i]);
	}
}

bool Base_Group::inGroup(std::shared_ptr<NPC> npc)
{
	for (int i = 0; i < NPCs.size(); i++)
	{
		if (NPCs[i] == npc)
			return true;
	}
	return false;
}

void Base_Group::updateScript()
{
	if (script.size() > 0)
		script.erase(script.begin());
}
void Base_Group::simulateConversation(SDL_Renderer* renderer, bool time, TTF_Font* font) {}

bool Base_Group::evaluateSpeaker()
{
	return false;
}

void Base_Group::setSpeaker() {}