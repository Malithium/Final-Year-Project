#pragma once
#include <vector>
#include "NPC.h"
#include "Group.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <memory>
#include <random>
class Base_Group
{
public:
	Base_Group();
	Base_Group(int x, int y, int size, std::string tBoxFile, std::string npcFile, SDL_Renderer* renderer, Topic tp);

	void renderConversation(SDL_Renderer* renderer);

	int getID();
	void setID(int id);
	bool AddToGroup(std::shared_ptr<NPC> nNPC);

	std::vector<Comment> getScript();

	bool isAvailable();
	std::pair<int, int> getSpace();
	void leaveSpace(std::shared_ptr<NPC> npc);
	bool joinSpace(std::shared_ptr<NPC> npc);
	void cleanUpGroup();

	int getLastSpoken();
	void setLastSpoken(int spoke);

	bool getIsReply();
	void setIsReply(bool reply);

	float getPolar();
	void setPolar(float polar);

	void updateScript();

	bool inGroup(std::shared_ptr<NPC> npc);

	int GetRandomNumber();

	virtual void simulateConversation(SDL_Renderer* renderer, bool time ,TTF_Font* font);
	virtual bool evaluateSpeaker();
	virtual void setSpeaker();

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

