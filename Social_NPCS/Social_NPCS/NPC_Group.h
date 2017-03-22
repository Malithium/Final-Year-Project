#pragma once

#include "Base_Group.h"

/**
* Created to hold a maximum group of 6 NPC's, it simulates the group conversation amongst the NPC's within the group.
*/
class NPC_Group : public Base_Group
{
public:
	NPC_Group(int x, int y, int size, std::string tBoxFile, std::string npcFile, SDL_Renderer* renderer, Topic tp);

	void simulateConversation(SDL_Renderer* renderer, bool time, TTF_Font* font);
	bool evaluateSpeaker();
	void setSpeaker();
};

