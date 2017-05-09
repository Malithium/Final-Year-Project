#include "User_Group.h"



User_Group::User_Group(int x, int y, int size, std::string tBoxFile, std::string npcFile, SDL_Renderer* renderer, Topic tp): Base_Group(x, y, size, tBoxFile, npcFile, renderer, tp)
{}

void User_Group::simulateConversation(SDL_Renderer* renderer, bool time, std::string boredomLevel,TTF_Font* font)
{
	// TODO: implement algorithm 2
}

bool User_Group::evaluateSpeaker()
{
	std::vector<std::shared_ptr<NPC>> NPCs = getNPCList();
	for (int i = 0; i < NPCs.size(); i++)
	{
		if (NPCs[i]->getSpeaking())
			return true;
	}
	return false;
}

void User_Group::setSpeaker(std::string boredomLevel)
{
	if (!evaluateSpeaker()) {
		int r = GetRandomNumber();
		std::vector<std::shared_ptr<NPC>> NPCs = getNPCList();
		std::vector<Comment> comms = getScript();
		for (int i = 0; i < NPCs.size(); i++)
		{
			if (NPCs[i]->getID() != NPCs[r]->getID())
			{
				std::string pred = NPCs[i]->getCurrentUser();
				/*
				if (std::find_if(comms.begin(), comms.end(), CommentComp(pred)) != comms.end())
				{

				};
				*/
			}
		}
		NPCs[r]->setSpeaking(true);
	}
}