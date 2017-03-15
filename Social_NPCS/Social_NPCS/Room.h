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


	std::pair<int, int> getRoomPosition(int pos);
	void LoadNPCs(SDL_Renderer* renderer);
	void LoadConversation(SDL_Renderer* renderer, bool time, TTF_Font* font);
	void HandleMove(SDL_Renderer* renderer);
	void generatePath(std::shared_ptr<NPC> npc, SDL_Renderer* renderer);
	void basicPath(std::shared_ptr<NPC> npc, SDL_Renderer* renderer);
	int findOpenGroup(int exclude);
	void leaveGroup(std::shared_ptr<NPC> npc);
	void joinGroup(std::shared_ptr<NPC> npc, int id);
	void cleanUpGroups();

private:
	int roomWidth, roomHeight, roomX, roomY;

	std::vector<std::shared_ptr<NPC>> roomNPCs;
	std::vector<std::shared_ptr<NPC_Group>> roomGroups;
	std::vector<std::shared_ptr<Node>> roomNodes;
	std::string roomsubject;
};

