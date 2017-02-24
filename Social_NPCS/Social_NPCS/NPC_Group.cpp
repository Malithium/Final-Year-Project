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
		(npcIterator)->evaluateEmotionLevel();
		(npcIterator)->render(renderer);
	}
}


/*
returns the NPCs in the group
*/
std::vector<NPC> NPC_Group::getNPCList()
{
	return NPCs;
}

/*
a method that handles the background logic of the NPC conversation's within the group.
*/
void NPC_Group::ConversationSimulation(SDL_Renderer* renderer, bool timer, TTF_Font* font)
{
	//if the specfied amount of time has passed simulate conversation
	if (timer)
	{
			for (int i = 0; i < NPCs.size(); i++)
			{
				//if the current NPC is speaking
				if (NPCs[i].getSpeaking() == true)
				{
					//load the textbox and comment
					NPCs[i].LoadBox(renderer);
					if (NPCs[i].getReadingTopic())
					{
						NPCs[i].prepareComment(topicString, font);
						NPCs[i].setReadingTopic(false);
					}

					if (isReply)
					{
						NPCs[LastSpoken].applyEmotionLevel(polar);
					}
					//retrieve the amount of lines we are rendering
					int lines = NPCs[i].getLinesToRender();

					//if we have yet to reach the maximum amount of lines to render
					if (currentComment < lines)
					{
						//load the comment
						NPCs[i].LoadComment(renderer, currentComment, font);
						currentComment++;
					}
					else
					{
						//free up the speech box and comment
						LastSpoken = i;
						currentComment = 0;
						NPCs[i].setSpeaking(false);
						NPCs[i].freeBox();

						//get a random number between 0 and groupsize
						srand(time(NULL));
						int random = rand() % GroupSize;

						//if the random number matches our current NPC, change its value
						if (random == i)
						{
							if (random == GroupSize - 1)
								random--;
							else
								random++;
						}

						//set the next NPC to speak and prepare its comment
						if (script.size() > 0)
						{
							NPCs[random].setSpeaking(true);
							NPCs[random].prepareComment(script[0].getBody(), font);
							isReply = script[0].getReply();
							polar = script[0].getPolarity();
							//remove the comment that was just rendered
							script.erase(script.begin());
						}
					}
				}
			}
	}
}

/*
renders the textbox and comments of the NPC's
*/
void NPC_Group::renderConversation(SDL_Renderer* renderer)
{
	std::vector<NPC>::iterator npcIterator;
	for (npcIterator = NPCs.begin(); npcIterator != NPCs.end(); npcIterator++)
	{
		//render the comment of the NPC currently speaking
		if (npcIterator->getSpeaking()) {
			(npcIterator)->renderBox(renderer);
			(npcIterator)->renderComment(renderer);
		}
	}
}