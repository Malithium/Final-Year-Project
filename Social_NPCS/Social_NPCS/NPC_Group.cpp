#include "NPC_Group.h"



NPC_Group::NPC_Group(int x, int y, int size) : GroupX(x), GroupY(y), GroupSize(size){}


void NPC_Group::createGroup(SDL_Renderer* renderer)
{
	populateVector();
	LoadGroup(renderer);
}

void NPC_Group::populateVector()
{
	int currentX = GroupX;
	int currentY = GroupY;
	if (GroupSize > 0)
	{
		for (int i = 0; i < GroupSize; i++)
		{
			Sprite nNPC(currentX, currentY);
			NPCs.push_back(nNPC);
			currentX += 35;
		}
	}
}

void NPC_Group::LoadGroup(SDL_Renderer* renderer)
{
	std::vector<Sprite>::iterator npcIterator;
	for (npcIterator = NPCs.begin(); npcIterator != NPCs.end(); npcIterator++)
	{
		(npcIterator)->loadMedia(renderer, "NPC.png");
	}
}

void NPC_Group::renderGroup(SDL_Renderer* renderer)
{
	std::vector<Sprite>::iterator npcIterator;
	for (npcIterator = NPCs.begin(); npcIterator != NPCs.end(); npcIterator++)
	{
		(npcIterator)->render(renderer);
	}
}

std::vector<Sprite> NPC_Group::getNPCList()
{
	return NPCs;
}
