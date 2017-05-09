#include "NPC_Group.h"

NPC_Group::NPC_Group(int x, int y, int size, std::string tBoxFile, std::string npcFile, SDL_Renderer* renderer, Topic tp): Base_Group(x, y, size, tBoxFile, npcFile, renderer, tp)
{}

/**
* This method is the implementation of Algorithm 1, which makes use of a script and anonymous NPCs
*/
void NPC_Group::simulateConversation(SDL_Renderer* renderer, bool time, std::string boredomLevel,TTF_Font* font)
{
	// if the neccecary amount of time has passed, run the simulation code
	if (time)
	{
		// set the speaker of the conversation
		setSpeaker(boredomLevel);

		std::vector<std::shared_ptr<NPC>> NPCs = getNPCList();
		for (int i = 0; i < NPCs.size(); i++)
		{
			std::shared_ptr<NPC> npc = NPCs[i];
			//check if the script has ended
			if (getScript().size() > 0)
			{
				//ignore all idle NPCs
				if (!npc->getIdle())
				{
					//get the NPC who is set to speak
					if (npc->getSpeaking())
					{
						// if the NPC is not reading, then assign him a fresh comment
						if (!npc->getReading())
						{
							npc->LoadBox(renderer);
							npc->setText(getScript()[0].getBody());
							npc->prepareComment(getScript()[0].getBody(), font);
							npc->setReading(true);
						}

						if (npc->getReading())
						{
							// get the number of lines thats is being rendered to the screen
							int lines = npc->getLinesToRender();
							if (npc->getCurrentLine() < lines)
							{
								// load the NPCs comment as a texture
								npc->LoadComment(renderer, npc->getCurrentLine(), font);
								npc->setCurrentLine(npc->getCurrentLine() + 1);
							}
							else
							{
								if (getIsReply())
								{
									// if this comment is a reply, apply the sentiment score to the previous speaker
									if (getLastSpoken() < getNPCList().size())
										NPCs[getLastSpoken()]->applyEmotionLevel(getPolar());
								}

								//the NPC has finished reading, so set him to not speak, and update conversation values
								npc->setSpeaking(false);
								npc->setReading(false);
								setIsReply(getScript()[0].getReply());
								setPolar(getScript()[0].getPolarity());
								setLastSpoken(i);
								npc->setCurrentLine(0);
								updateScript();
								setSpeaker(boredomLevel);
							}
						}
					}
				}
				else
				{
					// if the NPC is idle, he is not part of the conversation, and cant speak
					if (npc->getSpeaking())
					{
						npc->setSpeaking(false);
					}
				}
			}
			else
			{
				// if there is no script there is not conversation, so there cant be a speaker.
				npc->setSpeaking(false);
				npc->setReading(false);
				setLastSpoken(i);
				npc->setCurrentLine(0);
				npc->freeBox();
			}
		}
	}
}

/**
* This method checks if someone has already been selected to speak
*/
bool NPC_Group::evaluateSpeaker()
{
	std::vector<std::shared_ptr<NPC>> NPCs = getNPCList();
	for (int i = 0; i < NPCs.size(); i++)
	{
		// if there is already a speaker return true
		if (NPCs[i]->getSpeaking())
			return true;
	}
	return false;
}

/**
* set's the next speaker of the conversation, also applys boredom to the other NPCs
*/
void NPC_Group::setSpeaker(std::string boredomLevel)
{
	if (!evaluateSpeaker()) {
		// get a random number
		int r = GetRandomNumber();
		std::vector<std::shared_ptr<NPC>> NPCs = getNPCList();
		for (int i = 0; i < NPCs.size(); i++)
		{
			// if the NPC does not match the chosen speaker, increment their boredom levels
			if (NPCs[i]->getID() != NPCs[r]->getID())
			{
				int bored = NPCs[i]->getBoredom() + 1;
				NPCs[i]->setBoredom(bored);

				// if the boredom level surpasses the global boredom threshhold, set the NPC to idle
				if (NPCs[i]->getBoredom() > atoi(boredomLevel.c_str()))
				{
					NPCs[i]->setIdle(true);
				}
			}
		}

		// set the speakers boredom to 0
		NPCs[r]->setSpeaking(true);
		NPCs[r]->setBoredom(0);
	}
}