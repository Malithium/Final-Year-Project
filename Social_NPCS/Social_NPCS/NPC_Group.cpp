#include "NPC_Group.h"



enum positions
{
	TOP = 0,
	TOP_LEFT = 1,
	BOT_LEFT = 2,
	BOT = 3,
	BOT_RIGHT = 4,
	TOP_RIGHT = 5
};

NPC_Group::NPC_Group(int x, int y, int size, SDL_Renderer* renderer, Topic tp) : GroupX(x), GroupY(y), GroupSize(size)
{
	script = tp.getComments();
	for (int i = 0; i < GroupSize; i++)
	{
		switch (i)
		{
		case 0:
		{
			NPC nNPC("TextBox.png", "NPC.png", tp.getTopic(), renderer, GroupX, GroupY - 35);
			nNPC.setSpeaking(true);
			NPCs.push_back(nNPC);
			break;
		}
		case 1:
		{
			NPC nNPC("TextBox.png", "NPC.png", script[i-1].getBody(), renderer, GroupX + 35, GroupY - 17);
			NPCs.push_back(nNPC);
			script.erase(script.begin() + i - 1);
			break;
		}
		case 2:
		{
			NPC nNPC("TextBox.png", "NPC.png", script[i-2].getBody(), renderer, GroupX + 35, GroupY + 17);
			NPCs.push_back(nNPC);
			script.erase(script.begin() + i - 2);
			break;
		}
		case 3:
		{
			NPC nNPC("TextBox.png", "NPC.png", script[i - 3].getBody(), renderer, GroupX, GroupY + 35);
			NPCs.push_back(nNPC);
			script.erase(script.begin() + i - 3);
			break;
		}
		case 4:
		{
			NPC nNPC("TextBox.png", "NPC.png", script[i - 4].getBody(), renderer, GroupX -35, GroupY + 17);
			NPCs.push_back(nNPC);
			script.erase(script.begin() + i - 4);
			break;
		}
		case 5:
		{
			NPC nNPC("TextBox.png", "NPC.png", script[i - 5].getBody(), renderer, GroupX - 35, GroupY - 17);
			NPCs.push_back(nNPC);
			script.erase(script.begin() + i - 5);
			break;
		}
		}
	}
}



void NPC_Group::LoadNPCs(SDL_Renderer* renderer)
{
	std::vector<NPC>::iterator npcIterator;
	for (npcIterator = NPCs.begin(); npcIterator != NPCs.end(); npcIterator++)
	{
		(npcIterator)->render(renderer);
	}
}

std::vector<NPC> NPC_Group::getNPCList()
{
	return NPCs;
}

void NPC_Group::ConversationSimulation(SDL_Renderer* renderer, bool time)
{
	if (time)
	{
		for (int i = 0; i < NPCs.size(); i++)
		{
			if (NPCs[i].getSpeaking() == true)
			{
				int lines = NPCs[i].getLinesToRender();
				if (currentComment < lines)
				{
					NPCs[i].LoadBox(renderer);
					NPCs[i].LoadComment(renderer, currentComment);
					currentComment++;
				}
				else
				{
					currentComment = 0;
					NPCs[i].setSpeaking(false);
					NPCs[i].freeComment();
					NPCs[i].prepareComment(script[0].getBody());
					script.erase(script.begin());
					if (i + 1 < NPCs.size())
					{
						NPCs[i + 1].setSpeaking(true);
					}
					else
					{
						NPCs[0].setSpeaking(true);
					}
				}
			}
		}
	}
}

void NPC_Group::renderConversation(SDL_Renderer* renderer)
{
	for (int i = 0; i < NPCs.size(); i++)
	{
		if (NPCs[i].getSpeaking() == true)
		{
			NPCs[i].renderBox(renderer);
			NPCs[i].renderComment(renderer);
		}
	}
}