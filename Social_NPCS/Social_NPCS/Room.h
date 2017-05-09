#pragma once
#include <memory>
#include "NPC_Group.h"
#include "Node.h"
#include <math.h> 
class Room
{
public:
	Room();
	Room(int groupNum, int x, int y, int width, int height, std::string NPCSprite, std::string TextBoxSprite, SDL_Renderer* renderer, Group grp);

	/// return the rooms positions
	std::pair<int, int> getRoomPosition(int pos);

	/// render the NPCs to the scene
	void LoadNPCs(SDL_Renderer* renderer);

	/// render the NPC conversations in the room
	void LoadConversation(SDL_Renderer* renderer, bool time, std::string boredomLevel, TTF_Font* font);

	/// handle NPC movement
	void HandleMove(SDL_Renderer* renderer);

	/// generate a basic path for the NPC to follow
	void basicPath(std::shared_ptr<NPC> npc, SDL_Renderer* renderer);

	/// return the id of any open groups
	int findOpenGroup(int exclude);

	/// remove an npc from a group
	void leaveGroup(std::shared_ptr<NPC> npc);

	/// add an npc to a group
	void joinGroup(std::shared_ptr<NPC> npc, int id);

	/// check if any groups have finished conversing
	bool checkGroup(int id);

	/// remove any inactive groups
	void cleanUpGroups();

private:
	int roomWidth, roomHeight, roomX, roomY;

	std::vector<std::shared_ptr<NPC>> roomNPCs;
	std::vector<std::shared_ptr<Base_Group>> roomGroups;
	std::vector<std::shared_ptr<Node>> roomNodes;
	std::string roomsubject;
};

