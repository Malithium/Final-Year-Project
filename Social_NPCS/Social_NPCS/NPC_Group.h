#pragma once
#include <vector>
#include "NPC.h"
#include "Group.h"
#include <algorithm>

class NPC_Group
{
public:
	NPC_Group(int x, int y, int size, SDL_Renderer* renderer, Topic tp);

	void LoadNPCs(SDL_Renderer* renderer);
	void renderConversation(SDL_Renderer* renderer);
	void ConversationSimulation(SDL_Renderer* renderer, bool time);
	std::vector<NPC> getNPCList();
private:
	std::vector<NPC> NPCs;
	std::vector<Comment> script;

	int currentComment = 0;

	int GroupX;
	int GroupY;
	int GroupSize;
};

