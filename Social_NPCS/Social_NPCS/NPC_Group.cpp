#include "NPC_Group.h"
/*
The NPC_Group class is designed to represent a maximum group of 6 NPC's.
the specfied NPC's are initialised when the group is initialised.
*/
NPC_Group::NPC_Group(int x, int y, int size, std::string tBoxFile, std::string npcFile, SDL_Renderer* renderer, Topic tp) : GroupX(x), GroupY(y), GroupSize(size)
{
	script = tp.getComments();
	topicString = tp.getTopic();
	for (int i = 0; i < GroupSize; i++)
	{
		switch (i)
		{
		case 0:
		{
			NPC nNPC(tBoxFile, npcFile, "", renderer, GroupX, GroupY - 35);
			nNPC.setSpeaking(true);
			nNPC.setReadingTopic(true);
			NPCs.push_back(nNPC);
			break;
		}
		case 1:
		{
			NPC nNPC(tBoxFile, npcFile, "", renderer, GroupX + 35, GroupY - 17);
			NPCs.push_back(nNPC);
			break;
		}
		case 2:
		{
			NPC nNPC(tBoxFile, npcFile, "", renderer, GroupX + 35, GroupY + 17);
			NPCs.push_back(nNPC);
			break;
		}
		case 3:
		{
			NPC nNPC(tBoxFile, npcFile, "", renderer, GroupX, GroupY + 35);
			NPCs.push_back(nNPC);
			break;
		}
		case 4:
		{
			NPC nNPC(tBoxFile, npcFile, "", renderer, GroupX -35, GroupY + 17);
			NPCs.push_back(nNPC);
			break;
		}
		case 5:
		{
			NPC nNPC(tBoxFile, npcFile, "", renderer, GroupX - 35, GroupY - 17);
			NPCs.push_back(nNPC);
			break;
		}
		}
	}
}


/*
call each of the NPC's render functions to render each of there sprites to the screen.
*/
void NPC_Group::LoadNPCs(SDL_Renderer* renderer)
{
	std::vector<NPC>::iterator npcIterator;
	for (npcIterator = NPCs.begin(); npcIterator != NPCs.end(); npcIterator++)
	{
		(npcIterator)->loadMedia(renderer);
		(npcIterator)->render(renderer);	
	}
}

std::vector<NPC> NPC_Group::getNPCList()
{
	return NPCs;
}

/*
a method that handles the background logic of the NPC conversation's within the group.
*/
void NPC_Group::ConversationSimulation(SDL_Renderer* renderer, bool timer, TTF_Font* font)
{
	//if the specfied amount of time has passed
	if (timer)
	{
			for (int i = 0; i < NPCs.size(); i++)
			{
				if (NPCs[i].getSpeaking() == true)
				{
					NPCs[i].LoadBox(renderer);
					if (NPCs[i].getReadingTopic())
					{
						NPCs[i].prepareComment(topicString, font);
						NPCs[i].setReadingTopic(false);
					}

					int lines = NPCs[i].getLinesToRender();
					if (currentComment < lines)
					{
						NPCs[i].LoadComment(renderer, currentComment, font);
						currentComment++;
					}
					else
					{
						currentComment = 0;
						NPCs[i].setSpeaking(false);
						NPCs[i].freeBox();

						srand(time(NULL));
						int random = rand() % 6;

						if (random != i)
						{
							NPCs[random].setSpeaking(true);
							NPCs[random].prepareComment(script[0].getBody(), font);
							script.erase(script.begin());
						}
						else
						{
							if (random == 5)
								random--;
							else
								random++;
							NPCs[random].setSpeaking(true);
							NPCs[random].prepareComment(script[0].getBody(), font);
							script.erase(script.begin());
						}
					}
				}			
		}
	}
}

void NPC_Group::renderConversation(SDL_Renderer* renderer)
{
	std::vector<NPC>::iterator npcIterator;
	for (npcIterator = NPCs.begin(); npcIterator != NPCs.end(); npcIterator++)
	{
		if (npcIterator->getSpeaking()) {
			(npcIterator)->renderBox(renderer);
			(npcIterator)->renderComment(renderer);
		}
	}
}