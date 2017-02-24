#pragma once
#include <vector>
#include "NPC.h"
#include "Group.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
class NPC_Group
{
public:
	NPC_Group(int x, int y, int size, std::string tBoxFile, std::string npcFile, SDL_Renderer* renderer, Topic tp);

	void LoadNPCs(SDL_Renderer* renderer);
	void renderConversation(SDL_Renderer* renderer);
	void ConversationSimulation(SDL_Renderer* renderer, bool timer, TTF_Font* font);
	std::vector<NPC> getNPCList();
private:
	std::vector<NPC> NPCs;
	std::vector<Comment> script;

	std::string topicString;
	int currentComment = 0;

	bool isReply;
	int LastSpoken;
	float polar;

	int GroupX;
	int GroupY;
	int GroupSize;
};

