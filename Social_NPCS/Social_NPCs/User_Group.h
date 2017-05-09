#pragma once
#include "Base_Group.h"

class User_Group: public Base_Group
{
public:
	User_Group(int x, int y, int size, std::string tBoxFile, std::string npcFile, SDL_Renderer* renderer, Topic tp);

	void simulateConversation(SDL_Renderer* renderer, bool time, std::string boredomLevel, TTF_Font* font);
	bool evaluateSpeaker();
	void setSpeaker(std::string boredomLevel);
};

