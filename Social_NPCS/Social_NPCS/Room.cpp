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
		// Get a random number for the number of NPCs
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> distGroup(2, 6);
		int random = distGroup(rng);

		// Get an availale position in the room
		std::pair<int, int> positions = getRoomPosition(i);

		// Create a group within the room
		std::shared_ptr<Base_Group> group(new NPC_Group(positions.first, positions.second, random, TextBoxSprite, NPCSprite, renderer, grp.getTopics()[i]));
		
		// Generate a random number if NPCs and add them to the new group
		for (int n = 0; n < random; n++)
		{
			std::shared_ptr<NPC> nNPC(new NPC(TextBoxSprite, NPCSprite, "", renderer, 0, 0));
			nNPC->setID(id);
			nNPC->setGroupID(groupID);
			group->AddToGroup(nNPC);
			roomNPCs.push_back(nNPC);
			id++;
		}

		// Set the group ID
		group->setID(groupID);

		// Add the group to the room
		roomGroups.push_back(group);
		groupID++;

		// Surround the group with Nodes
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

/**
* Returns a pair of integers that hold the X and Y of the available room spaces.
*/
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

/**
* Call each of the NPC's render functions to render each of there sprites to the screen.
*/
void Room::LoadNPCs(SDL_Renderer* renderer)
{
	std::vector<std::shared_ptr<NPC>>::iterator npcIterator;
	for (npcIterator = roomNPCs.begin(); npcIterator != roomNPCs.end(); npcIterator++)
	{
		(*npcIterator)->loadMedia(renderer);
		(*npcIterator)->evaluateEmotionLevel();
		(*npcIterator)->render(renderer);
	}
}

/**
* Simulate and render each conversation happening in the room
*/
void Room::LoadConversation(SDL_Renderer* renderer, bool time, std::string boredomLevel, TTF_Font* font)
{
	std::vector<std::shared_ptr<Base_Group>>::iterator groupIterator;
	for (groupIterator = roomGroups.begin(); groupIterator != roomGroups.end(); groupIterator++)
	{
		(*groupIterator)->simulateConversation(renderer, time, boredomLevel, font);
		(*groupIterator)->renderConversation(renderer);
	}
}

/**
* Checks if any groups have any available space
*/
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

/**
* Removes an NPC from a group
*/
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

/**
* Adds an NPC to a group
*/
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

/**
* Check if a group exists in the room
*/
bool Room::checkGroup(int id)
{
	for (int i = 0; i < roomGroups.size(); i++)
	{
		if (roomGroups[i]->getID() == id)
			return true;
	}
	return false;
}

/**
* Handles the NPCs movement between groups
*/
void Room::HandleMove(SDL_Renderer* renderer)
{
	for (int i = 0; i < roomNPCs.size(); i++)
	{
		// Check if the NPCs group is still active
		bool gCheck = checkGroup(roomNPCs[i]->getGroupID());
		if (roomNPCs[i]->getGroupID() == -1 || !gCheck)
		{
			roomNPCs[i]->setIdle(true);
		}

		// Check if an NPC is currently idle
		if (roomNPCs[i]->getIdle())
		{
			if (!roomNPCs[i]->getMoving())
			{
				// Remove any groups in the scene that are no longer active
				cleanUpGroups();

				// Check if an NPCs group exists in the room
				int gID = findOpenGroup(roomNPCs[i]->getGroupID());
				if (gID > -1)
				{
					// Remove the NPC from the his current group
					leaveGroup(roomNPCs[i]);

					// Move the NPC to a new group
					joinGroup(roomNPCs[i], gID);	

					// Call the basic move method and set the NPC to move
					basicPath(roomNPCs[i], renderer);
					roomNPCs[i]->setMoving(true);

					// Free up any lingereing speech the NPC had left from the previous conversation
					roomNPCs[i]->freeBox();
				}

				// if there are no existing rooms, move the NPC off the screen to be deleted.
				if (gID == -1)
				{
					leaveGroup(roomNPCs[i]);
					roomNPCs[i]->setEndGoal(std::pair<int, int>(800, 800));
					basicPath(roomNPCs[i], renderer);
					roomNPCs[i]->setMoving(true);
					roomNPCs[i]->freeBox();
				}
			}
			else
			{
				// If an NPC is idle, call the movement method to start his movement process
				roomNPCs[i]->move();

				// Check if the NPC has met his end goal
				if (roomNPCs[i]->getX() == roomNPCs[i]->getEndGoal().first && roomNPCs[i]->getY() == roomNPCs[i]->getEndGoal().second)
				{
					// If the NPC has met his goal he is no longer idle or bored
					roomNPCs[i]->setIdle(false);
					roomNPCs[i]->setMoving(false);
					roomNPCs[i]->setBoredom(0);

					// If the NPC has reached here, then he is no longer in the room
					if (roomNPCs[i]->getX() == 800 && roomNPCs[i]->getY() == 800)
					{
						roomNPCs.erase(roomNPCs.begin() + i);
					}
				}
			}
		}
	}
}

/**
* Checks to see if any groups have finished their conversations and then removes them from the room
*/
void Room::cleanUpGroups()
{
	for (int g = 0; g < roomGroups.size(); g++)
	{
		if (roomGroups[g]->getScript().size() == 0)
		{
			for (int n = 0; n < roomNPCs.size(); n++)
			{
				if (roomNPCs[n]->getGroupID() == roomGroups[g]->getID()) {
					if (!(roomGroups[g]->inGroup(roomNPCs[n])))
					{
						roomNPCs[n]->setGroupID(-1);
						roomNPCs[n]->setIdle(true);
					}
				}
			}
			roomGroups[g]->cleanUpGroup();
			roomGroups.erase(roomGroups.begin() + g);
		}
	}
}

/**
* Creates a basic path for the NPC to walk to
*/
void Room::basicPath(std::shared_ptr<NPC> npc, SDL_Renderer* renderer)
{
	std::vector<std::shared_ptr<Node>> basicPath;
	basicPath.push_back(std::shared_ptr<Node>(new Node(npc->getEndGoal().first, npc->getEndGoal().second)));
	npc->setPath(basicPath);
	std::cout << "The goal Node for NPC: " << npc->getID() << " is: " << basicPath[0]->getX() << " , " << basicPath[0]->getY() << std::endl;
}
