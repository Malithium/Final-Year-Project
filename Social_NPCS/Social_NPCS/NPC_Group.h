#pragma once

#include "Base_Group.h"

/**
* The NPC_Group class is designed to represent a maximum group of 6 NPC's.
* the specfied NPC's are initialised when the group is initialised.
*/
class NPC_Group : public Base_Group
{
public:
	NPC_Group(int x, int y, int size, std::string tBoxFile, std::string npcFile, SDL_Renderer* renderer, Topic tp);

	void simulateConversation(SDL_Renderer* renderer, bool time, std::string boredomLevel,TTF_Font* font);
	bool evaluateSpeaker();
	void setSpeaker(std::string boredomLevel);
};

