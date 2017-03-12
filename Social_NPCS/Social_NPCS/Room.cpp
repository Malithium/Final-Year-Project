#include "Room.h"



Room::Room(){}

Room::Room(int groupNum, int x, int y, int width, int height, std::string NPCSprite, std::string TextBoxSprite, SDL_Renderer* renderer, Group grp)
{
	roomWidth = width;
	roomHeight = height;
	roomX = x;
	roomY = y;
	for (int i = 0; i < groupNum; i++)
	{
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> distGroup(2, 6);
		int random = distGroup(rng);

		std::pair<int, int> positions = getRoomPosition(i);
		std::shared_ptr<NPC_Group> group(new NPC_Group(positions.first, positions.second, random, TextBoxSprite, NPCSprite, renderer, grp.getTopics()[i]));

		for (int n = 0; n < random; n++)
		{
			std::shared_ptr<NPC> nNPC(new NPC(TextBoxSprite, NPCSprite, "", renderer, 0, 0));
			group->AddToGroup(nNPC);
			roomNPCs.push_back(nNPC);
		}
		roomGroups.push_back(group);
		std::shared_ptr<Node> node1(new Node(positions.first - 50, positions.second - 50));
		std::shared_ptr<Node> node2(new Node(positions.first + 80, positions.second - 50));
		std::shared_ptr<Node> node3(new Node(positions.first - 50, positions.second + 80));
		std::shared_ptr<Node> node4(new Node(positions.first + 80, positions.second + 80));
		roomNodes.push_back(node1);
		roomNodes.push_back(node2);
		roomNodes.push_back(node3);
		roomNodes.push_back(node4);
	}
}

std::pair<int, int> Room::getRoomPosition(int pos)
{
	std::pair<int, int> XYPos;
	switch (pos)
	{
	case 0:
		XYPos.first = roomWidth / 2;
		XYPos.second = roomHeight / 2;
		break;
	case 1:
		XYPos.first = roomWidth - roomX;
		XYPos.second = roomHeight - roomY;
		break;
	case 2:
		XYPos.first = roomX;
		XYPos.second = roomY;
		break;
	case 3:
		XYPos.first = roomWidth - roomX;
		XYPos.second = roomY;
		break;
	case 4:
		XYPos.first = roomX;
		XYPos.second = roomHeight - roomY;
		break;
	}

	return XYPos;
}

/*
call each of the NPC's render functions to render each of there sprites to the screen.
*/
void Room::LoadNPCs(SDL_Renderer* renderer)
{
	std::vector<std::shared_ptr<NPC>>::iterator npcIterator;
	for (npcIterator = roomNPCs.begin(); npcIterator != roomNPCs.end(); npcIterator++)
	{
		(*npcIterator)->loadMedia(renderer);
		(*npcIterator)->setBBox((*npcIterator)->getX(), (*npcIterator)->getY(), (*npcIterator)->getWidth(), (*npcIterator)->getHeight());
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		SDL_Rect box = (*npcIterator)->getBBox();
		SDL_RenderDrawRect(renderer, &box);
		(*npcIterator)->evaluateEmotionLevel();
		(*npcIterator)->render(renderer);
	}
}

void Room::LoadConversation(SDL_Renderer* renderer, bool time, TTF_Font* font)
{
	std::vector<std::shared_ptr<NPC_Group>>::iterator groupIterator;
	for (groupIterator = roomGroups.begin(); groupIterator != roomGroups.end(); groupIterator++)
	{
		(*groupIterator)->ConversationSimulation(renderer, time, font);
		(*groupIterator)->renderConversation(renderer);
		(*groupIterator)->CheckBoredom();
	}
}

void Room::CheckIdleNPCs(SDL_Renderer* renderer)
{
	std::vector<std::shared_ptr<NPC>>::iterator npcIterator;
	for (npcIterator = roomNPCs.begin(); npcIterator != roomNPCs.end(); npcIterator++)
	{
		if ((*npcIterator)->getIdle() == true && (*npcIterator)->getPath().size() == 0)
		{
			std::mt19937 rng;
			rng.seed(std::random_device()());
			std::uniform_int_distribution<std::mt19937::result_type> distGroup(0, roomGroups.size()-1);
			int random = distGroup(rng);
			bool sameGroup = false;

			for (int i = 0; i < roomGroups[random]->getNPCList().size(); i++)
			{
				if ((*npcIterator)->getX() == roomGroups[random]->getNPCList()[i]->getX() && (*npcIterator)->getY() == roomGroups[random]->getNPCList()[i]->getY())
				{
					sameGroup = true;
				}
			}

			if (sameGroup)
			{
				if (random >= roomGroups.size())
					random--;
				else
					random++;
			}

			if (roomGroups.size()-1 > 0 && roomGroups[random]->getNPCList().size() < 6)
			{
				std::pair<int, int> newPosition = roomGroups[random]->getGroupPositions(roomGroups[random]->getNPCList().size());
				(*npcIterator)->setEndGoal(newPosition);
				if((*npcIterator)->getPath().size() == 0)
					generatePath((*npcIterator), renderer);
			}
		}
	}
}

void Room::generatePath(std::shared_ptr<NPC> npc, SDL_Renderer* renderer)
{
	
}