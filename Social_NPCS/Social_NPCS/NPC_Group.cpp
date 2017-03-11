#include "NPC_Group.h"
/*
The NPC_Group class is designed to represent a maximum group of 6 NPC's.
the specfied NPC's are initialised when the group is initialised.
*/
NPC_Group::NPC_Group(int x, int y, int size, std::string tBoxFile, std::string npcFile, SDL_Renderer* renderer, Topic tp) : GroupX(x), GroupY(y), GroupSize(size)
{
	script = tp.getComments();
	topicString = tp.getTopic();
}

std::pair<int, int> NPC_Group::getGroupPositions(int pos)
{
	std::pair<int, int> XYPos;
	switch (pos)
	{
	case 0:
		XYPos.first = GroupX;
		XYPos.second = GroupY - 35;
		break;
	case 1:
		XYPos.first = GroupX + 35;
		XYPos.second = GroupY - 17;
		break;
	case 2:
		XYPos.first = GroupX + 35;
		XYPos.second = GroupY + 17;
		break;
	case 3:
		XYPos.first = GroupX;
		XYPos.second = GroupY + 35;
		break;
	case 4:
		XYPos.first = GroupX - 35;
		XYPos.second = GroupY + 17;
		break;
	case 5:
		XYPos.first = GroupX - 35;
		XYPos.second = GroupY - 17;
		break;
	}

	return XYPos;
}

void NPC_Group::AddToGroup(std::shared_ptr<NPC> nNPC)
{
	if (NPCs.size() < 6)
	{
		std::pair<int, int> XYPos = getGroupPositions(NPCs.size());
		nNPC->setX(XYPos.first);
		nNPC->setY(XYPos.second);
		if (NPCs.size() == 0)
		{
			nNPC->setSpeaking(true);
			nNPC->setReadingTopic(true);
		}
		NPCs.push_back(nNPC);
	}
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
						EvaluateGroupBoredom();
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
				NPCs[random]->setBoredom(0);
				isReply = script[0].getReply();
				polar = script[0].getPolarity();

				//remove the comment that was just rendered
				script.erase(script.begin());
				speakerDesignated = true;
			}
		}
	}
}

/**
* checks which NPCs are bored
*/
void NPC_Group::CheckBoredom()
{
	for (int n = 0; n < NPCs.size(); n++)
	{
		int bored = NPCs[n]->getBoredom();
		if (bored > 10)
		{
			NPCs[n]->freeBox();
			NPCs[n]->free();
			NPCs.erase(NPCs.begin() + n);
			GroupSize = NPCs.size();
		}
	}

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

int NPC_Group::GetRandomNumber()
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

	return random;
}

void NPC_Group::EvaluateGroupBoredom()
{
	for (int n = 0; n < NPCs.size(); n++)
	{
		if (!NPCs[n]->getSpeaking())
			NPCs[n]->setBoredom(NPCs[n]->getBoredom() + 1);
	}
}