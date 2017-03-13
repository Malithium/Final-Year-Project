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

	int getID();
	void setID(int id);

	bool AddToGroup(std::shared_ptr<NPC> nNPC);

	std::vector<Comment> getScript();

	bool isAvailable();
	std::pair<int, int> getSpace();
	void leaveSpace(std::shared_ptr<NPC> npc);
	bool joinSpace(std::shared_ptr<NPC> npc);

	int GetRandomNumber();
	void simulateConversation(SDL_Renderer* renderer, TTF_Font* font);
	bool evaluateSpeaker();
	void setSpeaker();

	std::vector<std::shared_ptr<NPC>> getNPCList();
private:
	std::vector<std::shared_ptr<NPC>> NPCs;
	std::vector<Comment> script;

	int ID;

	std::vector<std::pair<int, int>> availableSpace;

	bool speakerDesignated = false;
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

