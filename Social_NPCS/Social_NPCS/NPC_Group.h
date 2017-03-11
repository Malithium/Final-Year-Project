#pragma once
#include <vector>
#include "NPC.h"
#include "Group.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <memory>
#include <random>
/**
* Created to hold a maximum group of 6 NPC's, it simulates the group conversation amongst the NPC's within the group.
*/
class NPC_Group
{
public:
	NPC_Group(int x, int y, int size, std::string tBoxFile, std::string npcFile, SDL_Renderer* renderer, Topic tp);

	void renderConversation(SDL_Renderer* renderer);
	void ConversationSimulation(SDL_Renderer* renderer, bool timer, TTF_Font* font);
	void CheckBoredom();
	std::pair<int, int> getGroupPositions(int pos);

	void AddToGroup(std::shared_ptr<NPC> nNPC);

	int GetRandomNumber();
	void EvaluateGroupBoredom();

	std::vector<std::shared_ptr<NPC>> getNPCList();
private:
	std::vector<std::shared_ptr<NPC>> NPCs;
	std::vector<Comment> script;

	bool speakerDesignated = false;
	bool reading = false;
	bool topicRead = true;

	std::string topicString;
	int currentComment = 0;

	bool isReply;
	int lastSpoken;
	float polar;

	int GroupX;
	int GroupY;
	int GroupSize;
};

