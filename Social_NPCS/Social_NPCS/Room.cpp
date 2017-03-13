#include "Room.h"

Room::Room(){}

Room::Room(int groupNum, int x, int y, int width, int height, std::string NPCSprite, std::string TextBoxSprite, SDL_Renderer* renderer, Group grp)
{
	roomWidth = width;
	roomHeight = height;
	roomX = x;
	roomY = y;
	int id = 0;
	int groupID = 0;
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
			nNPC->setID(id);
			nNPC->setGroupID(groupID);
			group->AddToGroup(nNPC);
			roomNPCs.push_back(nNPC);
			id++;
		}
		group->setID(groupID);
		roomGroups.push_back(group);
		groupID++;
		std::shared_ptr<Node> node1(new Node(positions.first - 50, positions.second - 50));
		std::shared_ptr<Node> node2(new Node(positions.first + 80, positions.second - 50));
		std::shared_ptr<Node> node3(new Node(positions.first - 50, positions.second + 80));
		std::shared_ptr<Node> node4(new Node(positions.first + 80, positions.second + 80));
		roomNodes.push_back(node1);
		roomNodes.push_back(node2);
		roomNodes.push_back(node3);
		roomNodes.push_back(node4);
		int size = roomGroups[i]->getNPCList().size();
		std::cout << "Group of index " << i << " has: " << size << " NPCs" << std::endl;
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
	}
}
int Room::findOpenGroup(int exclude)
{
	for (int i = 0; i < roomGroups.size(); i++)
	{
		if (roomGroups[i]->isAvailable() && roomGroups[i]->getID() != exclude)
		{
			return roomGroups[i]->getID();
		}
	}
	return -1;
}

void Room::leaveGroup(std::shared_ptr<NPC> npc)
{
	for (int i = 0; i < roomGroups.size(); i++)
	{
		for (int n = 0; n < roomGroups[i]->getNPCList().size(); n++)
		{
			if (roomGroups[i]->getNPCList()[n]->getID() == npc->getID())
			{
				roomGroups[i]->leaveSpace(npc);
			}
		}
	}
}

void Room::joinGroup(std::shared_ptr<NPC> npc, int id)
{
	for (int i = 0; i < roomGroups.size(); i++)
	{
		if (roomGroups[i]->getID() == id)
		{
			roomGroups[i]->joinSpace(npc);
			npc->setMoving(true);
		}
	}
}
void Room::HandleMove(SDL_Renderer* renderer)
{
	for (int i = 0; i < roomNPCs.size(); i++)
	{
		if (roomNPCs[i]->getIdle())
		{
			if (!roomNPCs[i]->getMoving())
			{
				int gID = findOpenGroup(roomNPCs[i]->getGroupID());
				if (gID > -1)
				{
					leaveGroup(roomNPCs[i]);
					joinGroup(roomNPCs[i], gID);					
					basicPath(roomNPCs[i], renderer);
					roomNPCs[i]->setMoving(true);
					roomNPCs[i]->freeBox();
				}
			}
			else
			{
				roomNPCs[i]->move();
				if (roomNPCs[i]->getX() == roomNPCs[i]->getEndGoal().first && roomNPCs[i]->getY() == roomNPCs[i]->getEndGoal().second)
				{
					roomNPCs[i]->setIdle(false);
					roomNPCs[i]->setMoving(false);
					roomNPCs[i]->setBoredom(0);
				}
			}
		}
	}
}

void Room::basicPath(std::shared_ptr<NPC> npc, SDL_Renderer* renderer)
{
	std::vector<std::shared_ptr<Node>> basicPath;
	basicPath.push_back(std::shared_ptr<Node>(new Node(npc->getEndGoal().first, npc->getEndGoal().second)));
	npc->setPath(basicPath);
	std::cout << "The goal Node for NPC: " << npc->getID() << " is: " << basicPath[0]->getX() << " , " << basicPath[0]->getY() << std::endl;
}
/*
void Room::generatePath(std::shared_ptr<NPC> npc, SDL_Renderer* renderer)
{
	std::vector<std::shared_ptr<Node>> possibleNodes;
	std::vector<std::shared_ptr<Node>> finalPath;
	std::vector<std::shared_ptr<Node>> visitedNodes;

	std::vector<std::shared_ptr<Node>>::iterator possIterator;
	std::vector<std::shared_ptr<Node>>::iterator nodeIterator;
	std::vector<std::shared_ptr<Node>>::iterator finalIterator;
	std::vector<std::shared_ptr<Node>>::iterator visitedIterator;
	std::vector<std::shared_ptr<NPC>>::iterator NPCsIterator;

	bool canMakeGoal = false;
	while (!canMakeGoal)
	{
		//iterate over every node in the room
		for (nodeIterator = roomNodes.begin(); nodeIterator != roomNodes.end(); ++nodeIterator)
		{
			bool intersection = false;
			bool beenVisited = false;
			bool goalIntersection = false;


			//check if we have already visited the node
			if (visitedNodes.size() > 0)
			{
				for (visitedIterator = visitedNodes.begin(); visitedIterator != visitedNodes.end(); ++visitedIterator)
				{
					if ((*nodeIterator)->getX() == (*visitedIterator)->getX() && (*nodeIterator)->getY() == (*visitedIterator)->getY())
					{
						beenVisited = true;
					}
				}
			}

			if (!beenVisited)
			{
				//Iterate over every NPC in the room
				for (NPCsIterator = roomNPCs.begin(); NPCsIterator != roomNPCs.end(); ++NPCsIterator)
				{
					if (!((*NPCsIterator)->getX() == npc->getX() && (*NPCsIterator)->getY() == npc->getY()))
					{
						int baseX;
						int baseY;
						if (visitedNodes.size() == 0)
						{
							baseX = npc->getX() + (npc->getWidth() / 2);
							baseY = npc->getY() + (npc->getHeight() / 2);
						}
						else
						{
							baseX = visitedNodes[visitedNodes.size() - 1]->getX();
							baseY = visitedNodes[visitedNodes.size() - 1]->getY();
						}

						int x2 = (*nodeIterator)->getX();
						int y2 = (*nodeIterator)->getY();

						//checks for intersections between a line and a rect
						SDL_Rect npcBox = (*NPCsIterator)->getBBox();
						bool check = SDL_IntersectRectAndLine(&npcBox, &baseX, &baseY, &x2, &y2);
						if (check)
						{
							intersection = true;
						}

						int goalX = npc->getEndGoal().first;
						int goalY = npc->getEndGoal().second;

						bool goalCheck = SDL_IntersectRectAndLine(&npcBox, &baseX, &baseY, &goalX, &goalY);
						if (goalCheck)
						{
							goalIntersection = true;
						}
					}
				}
				if (!goalIntersection)
				{
					canMakeGoal = true;
				}
				if (!intersection)
				{
					possibleNodes.push_back((*nodeIterator));
				}
			}
		}
		

		if (!canMakeGoal)
		{
			//iterate over all possible nodes
			for (possIterator = possibleNodes.begin(); possIterator != possibleNodes.end(); ++possIterator)
			{
					std::vector<std::shared_ptr<Node>>::iterator nxtIter;
					int nextX = 0;
					int nextY = 0;
					if (possIterator != possibleNodes.end() && possIterator + 1 != possibleNodes.end())
					{
						nxtIter = possIterator; ++nxtIter;
						nextX = (*nxtIter)->getX();
						nextY = (*nxtIter)->getY();
					}

					//Our current position
					int baseX;
					int baseY;

					//The Node we are traveling to
					int currX = (*possIterator)->getX();
					int currY = (*possIterator)->getY();

					//The coordinates of the goal
					int goalX = npc->getEndGoal().first;
					int goalY = npc->getEndGoal().second;

					if (visitedNodes.size() == 0)
					{
						baseX = npc->getX() + (npc->getWidth() / 2);
						baseY = npc->getY() + (npc->getHeight() / 2);
					}
					else
					{
						baseX = visitedNodes[visitedNodes.size() - 1]->getX();
						baseY = visitedNodes[visitedNodes.size() - 1]->getY();
					}

					int distX = currX - baseX;
					int distY = currY - baseY;
					int toNodeLength = distX + distY;

					int goalDistX = nextX - goalX;
					int goalDistY = nextY - goalY;
					int toGoalLength = goalDistX + goalDistY;

					int eval1 = toNodeLength + toGoalLength;
					if (nextX != 0 && nextY != 0)
					{
						int nDistX = nextX - baseX;
						int nDistY = nextY - baseY;
						int nToNodeLength = nDistX + nDistY;

						int nGoalDistX = nextX - goalX;
						int nGoalDistY = nextY - goalY;
						int nToGoalLength = nGoalDistX + nGoalDistY;

						int eval2 = nToNodeLength + nToGoalLength;

						if (eval1 < eval2)
							possibleNodes.erase(possibleNodes.begin() + 1);
						else
							possibleNodes.erase(possibleNodes.begin());
					}
				}
			if (visitedNodes.size() > 0)
			{
				if (possibleNodes[0]->getX() == visitedNodes[visitedNodes.size() - 1]->getX() && possibleNodes[0]->getY() == visitedNodes[visitedNodes.size() - 1]->getY())
				{
					canMakeGoal = true;
					finalPath.push_back(std::shared_ptr<Node>(new Node(npc->getEndGoal().first, npc->getEndGoal().second)));
				}
				else
				{
					visitedNodes.push_back(possibleNodes[0]);
					finalPath.push_back(possibleNodes[0]);
					possibleNodes.clear();
				}
			}
			else
			{
				visitedNodes.push_back(possibleNodes[0]);
				finalPath.push_back(possibleNodes[0]);
				possibleNodes.clear();
			}
		}
		else
		{
			finalPath.push_back(std::shared_ptr<Node>(new Node(npc->getEndGoal().first, npc->getEndGoal().second)));
		}
	}

	npc->setPath(finalPath);
}
*/