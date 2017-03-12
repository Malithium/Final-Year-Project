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
		//(*groupIterator)->renderConversation(renderer);
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
	std::vector<std::shared_ptr<Node>> possibleNodes;
	std::vector<std::shared_ptr<Node>> finalPath;
	std::vector<std::shared_ptr<Node>> visitedNodes;

	std::vector<std::shared_ptr<Node>>::iterator possIterator;
	std::vector<std::shared_ptr<Node>>::iterator nodeIterator;
	std::vector<std::shared_ptr<Node>>::iterator finalIterator;
	std::vector<std::shared_ptr<Node>>::iterator visitedIterator;
	std::vector<std::shared_ptr<Node>>::iterator stdIterator;
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
					int toNodeLength = sqrt((distX*distX) + (distY*distY));

					int goalDistX = goalX - nextX;
					int goalDistY = goalY - nextY;
					int toGoalLength = sqrt((goalDistX*goalDistX) + (goalDistY*goalDistY));

					int eval1 = toNodeLength + toGoalLength;
					if (nextX != 0 && nextY != 0)
					{
						int nDistX = nextX - baseX;
						int nDistY = nextY - baseY;
						int nToNodeLength = sqrt((nDistX*nDistX) + (nDistY*nDistY));

						int nGoalDistX = goalX - nextX;
						int nGoalDistY = goalY - nextY;
						int nToGoalLength = sqrt((nGoalDistX*nGoalDistX) + (nGoalDistY*nGoalDistY));

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
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	for (stdIterator = finalPath.begin(); stdIterator != finalPath.end(); ++stdIterator)
	{
		std::vector<std::shared_ptr<Node>>::iterator nxtIter;
		if (stdIterator != finalPath.end() && stdIterator + 1 != finalPath.end())
		{
			nxtIter = stdIterator; ++nxtIter;
			if (stdIterator == finalPath.begin())
				SDL_RenderDrawLine(renderer, npc->getX() + (npc->getWidth() / 2), npc->getY() + (npc->getHeight() / 2), (*stdIterator)->getX(), (*stdIterator)->getY());

			SDL_RenderDrawLine(renderer, (*stdIterator)->getX(), (*stdIterator)->getY(), (*nxtIter)->getX(), (*nxtIter)->getY());
		}		
	}
	SDL_Rect endPoint;
	endPoint.h = 10;
	endPoint.w = 10;
	endPoint.x = finalPath[finalPath.size() - 1]->getX();
	endPoint.y = finalPath[finalPath.size() - 1]->getY();
	SDL_RenderDrawRect(renderer, &endPoint);
	npc->setPath(finalPath);
}