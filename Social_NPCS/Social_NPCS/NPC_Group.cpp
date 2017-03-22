#include "NPC_Group.h"
/*
The NPC_Group class is designed to represent a maximum group of 6 NPC's.
the specfied NPC's are initialised when the group is initialised.
*/
NPC_Group::NPC_Group(int x, int y, int size, std::string tBoxFile, std::string npcFile, SDL_Renderer* renderer, Topic tp): Base_Group(x, y, size, tBoxFile, npcFile, renderer, tp)
{}

void NPC_Group::simulateConversation(SDL_Renderer* renderer, bool time, TTF_Font* font)
{
	if (time)
	{
		setSpeaker();
		std::vector<std::shared_ptr<NPC>> NPCs = getNPCList();
		for (int i = 0; i < NPCs.size(); i++)
		{
			std::shared_ptr<NPC> npc = NPCs[i];
			if (getScript().size() > 0)
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
							npc->setText(getScript()[0].getBody());
							npc->prepareComment(getScript()[0].getBody(), font);
							npc->setReading(true);
						}

						if (npc->getReading())
						{
							int lines = npc->getLinesToRender();
							if (npc->getCurrentLine() < lines)
							{
								npc->LoadComment(renderer, npc->getCurrentLine(), font);
								npc->setCurrentLine(npc->getCurrentLine() + 1);
							}
							else
							{
								if (getIsReply())
								{
									if (getLastSpoken() < getNPCList().size())
										NPCs[getLastSpoken()]->applyEmotionLevel(getPolar());
								}
								npc->setSpeaking(false);
								npc->setReading(false);
								setIsReply(getScript()[0].getReply());
								setPolar(getScript()[0].getPolarity());
								setLastSpoken(i);
								npc->setCurrentLine(0);
								updateScript();
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
				setLastSpoken(i);
				npc->setCurrentLine(0);
				npc->freeBox();
			}
		}
	}
}

bool NPC_Group::evaluateSpeaker()
{
	std::vector<std::shared_ptr<NPC>> NPCs = getNPCList();
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
		std::vector<std::shared_ptr<NPC>> NPCs = getNPCList();
		for (int i = 0; i < NPCs.size(); i++)
		{
			if (NPCs[i]->getID() != NPCs[r]->getID())
			{
				int bored = NPCs[i]->getBoredom() + 1;
				NPCs[i]->setBoredom(bored);
				if (NPCs[i]->getBoredom() > 13)
				{
					NPCs[i]->setIdle(true);
				}
			}
		}
		NPCs[r]->setSpeaking(true);
		NPCs[r]->setBoredom(0);
	}
}