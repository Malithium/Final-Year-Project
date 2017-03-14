#include "NPC_Group.h"
/*
The NPC_Group class is designed to represent a maximum group of 6 NPC's.
the specfied NPC's are initialised when the group is initialised.
*/
NPC_Group::NPC_Group(int x, int y, int size, std::string tBoxFile, std::string npcFile, SDL_Renderer* renderer, Topic tp) : GroupX(x), GroupY(y), GroupSize(size)
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

bool NPC_Group::isAvailable()
{
	if (availableSpace.size() > 0)
		return true;
	else
		return false;
}

std::pair<int, int> NPC_Group::getSpace()
{
	if (isAvailable()) {
		std::pair<int, int> recoveredSpace = availableSpace[0];
		return recoveredSpace;
	}
}

bool NPC_Group::joinSpace(std::shared_ptr<NPC> npc)
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

int NPC_Group::getID()
{
	return ID;
}

void NPC_Group::setID(int id)
{
	ID = id;
}

void NPC_Group::leaveSpace(std::shared_ptr<NPC> npc)
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

bool NPC_Group::AddToGroup(std::shared_ptr<NPC> nNPC)
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

std::vector<Comment> NPC_Group::getScript()
{
	return script;
}

/*
returns the NPCs in the group
*/
std::vector<std::shared_ptr<NPC>> NPC_Group::getNPCList()
{
	return NPCs;
}

/*
a method that handles the background logic of the NPC conversation's within the group.
*/
void NPC_Group::ConversationSimulation(SDL_Renderer* renderer, bool timer, TTF_Font* font)
{

	if (timer)
	{
		simulateConversation(renderer, font);
		/*
		for (int i = 0; i < NPCs.size(); i++) {
			if (NPCs[i]->getSpeaking() == true)
			{
				if (!reading)
				{
					NPCs[i]->LoadBox(renderer);
					if (NPCs[i]->getReadingTopic())
					{
						NPCs[i]->prepareComment(topicString, font);
						NPCs[i]->setReadingTopic(false);						
					}
					reading = true;
				}
				
				if(reading)
				{
					//get the chunked comment from the NPC
					int lines = NPCs[i]->getLinesToRender();
					if (currentComment < lines)
					{
						//load the comment
						NPCs[i]->LoadComment(renderer, currentComment, font);
						currentComment++;
					}
					else
					{
						if (isReply && !(NPCs[i]->getReadingTopic()))
						{
							if(lastSpoken < NPCs.size())
								NPCs[lastSpoken]->applyEmotionLevel(polar);
						}
						reading = false;
						lastSpoken = i;
						currentComment = 0;
						NPCs[i]->setSpeaking(false);
						speakerDesignated = false;
						topicRead = false;
					}
				}
			}
		}
	}
	else
	{
		if (NPCs.size() == 1)
		{
			NPCs[0]->freeBox();
			NPCs[0]->free();
			NPCs.erase(NPCs.begin());
			GroupSize = NPCs.size();
		}
		bool speakCheck = false;
		if (speakerDesignated) {
			for (int p = 0; p < NPCs.size(); p++)
			{
				if (NPCs[p]->getSpeaking()) {
					speakCheck = true;
					break;
				}
			}
		}

		if (!speakCheck) {
			speakerDesignated = false;
		}

		if (speakerDesignated == false && topicRead == false)
		{
			int random = GetRandomNumber();

			//set the next NPC to speak and prepare its comment
			if (script.size() > 0)
			{
					NPCs[random]->setSpeaking(true);
					NPCs[random]->prepareComment(script[0].getBody(), font);
					NPCs[random]->setText(script[0].getBody());
					isReply = script[0].getReply();
					polar = script[0].getPolarity();

					//remove the comment that was just rendered
					script.erase(script.begin());
					speakerDesignated = true;
			}
		}
		*/
	}

}
void NPC_Group::simulateConversation(SDL_Renderer* renderer, TTF_Font* font)
{
	setSpeaker();
	for (int i = 0; i < NPCs.size(); i++)
	{
		std::shared_ptr<NPC> npc = NPCs[i];
		if (script.size() > 0)
		{
			//ignore all idle NPCs
			if (!npc->getIdle())
			{
				//get the NPC who is set to speak
				if (npc->getSpeaking())
				{
					if (!npc->getReading())
					{
						npc->LoadBox(renderer);
						npc->setText(script[0].getBody());
						npc->prepareComment(script[0].getBody(), font);
						npc->setReading(true);
					}
					
					if(npc->getReading())
					{
						int lines = npc->getLinesToRender();
						if (npc->getCurrentLine() < lines)
						{
							npc->LoadComment(renderer, npc->getCurrentLine(), font);
							npc->setCurrentLine(npc->getCurrentLine() + 1);
						}
						else
						{
							if (isReply)
							{
								if (lastSpoken < NPCs.size())
									NPCs[lastSpoken]->applyEmotionLevel(polar);
							}
							npc->setSpeaking(false);
							npc->setReading(false);
							isReply = script[0].getReply();
							polar = script[0].getPolarity();
							lastSpoken = i;
							npc->setCurrentLine(0);
							script.erase(script.begin());
							setSpeaker();
						}
					}
				}
			}
			else
			{
				if (npc->getSpeaking())
				{
					npc->setSpeaking(false);
				}
			}
		}
		else
		{
			npc->setSpeaking(false);
			npc->setReading(false);
			lastSpoken = i;
			npc->setCurrentLine(0);
			npc->freeBox();
		}
	}
}

bool NPC_Group::evaluateSpeaker()
{
	for (int i = 0; i < NPCs.size(); i++)
	{
		if (NPCs[i]->getSpeaking())
			return true;
	}
	return false;
}

void NPC_Group::setSpeaker()
{
	if (!evaluateSpeaker()) {
		int r = GetRandomNumber();
		for (int i = 0; i < NPCs.size(); i++)
		{
			if (NPCs[i]->getID() != NPCs[r]->getID())
			{
				int bored = NPCs[i]->getBoredom() + 1;
				NPCs[i]->setBoredom(bored);
				if (NPCs[i]->getBoredom() > 10)
				{
					NPCs[i]->setIdle(true);
				}
			}
		}
		NPCs[r]->setSpeaking(true);
		NPCs[r]->setBoredom(0);
	}
}

int NPC_Group::GetRandomNumber()
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
void NPC_Group::renderConversation(SDL_Renderer* renderer)
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

