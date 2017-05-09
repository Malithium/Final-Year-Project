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
* The Base class for the Group classes within the project
*/
class Base_Group
{
public:
	Base_Group();
	Base_Group(int x, int y, int size, std::string tBoxFile, std::string npcFile, SDL_Renderer* renderer, Topic tp);

	/// Renders the conversation to the SDL window.
	void renderConversation(SDL_Renderer* renderer);

	/// Retrieves the group ID.
	int getID();
	
	/// Set the group ID.
	void setID(int id);
	
	/// Add an NPC to the group.
	bool AddToGroup(std::shared_ptr<NPC> nNPC);

	/// Get the script of comments.
	std::vector<Comment> getScript();

	/// Checks to if there is any avaialbe space in the groups.
	bool isAvailable();
	
	/// Retrieves an open space from a group of NPC's.
	std::pair<int, int> getSpace();
	
	/// Called when the NPC wants to leave a group.
	void leaveSpace(std::shared_ptr<NPC> npc);
	
	/// Called when an NPC wants to join a group.
	bool joinSpace(std::shared_ptr<NPC> npc);
	
	/// Clean up call, called when the group has nothing to talk about.
	void cleanUpGroup();

	/// Get the last NPC who spoke in the conversation.
	int getLastSpoken();
	
	/// Set the last spoken NPC
	void setLastSpoken(int spoke);

	/// Check if the current comment is a reply.
	bool getIsReply();
	
	/// Set a bool to indicate the next comment is a reply.
	void setIsReply(bool reply);

	/// Get the NPC's polarity score
	float getPolar();
	
	/// Set the NPC's polarity score
	void setPolar(float polar);

	/// Update the script.
	void updateScript();

	/// Returns a bool to indicate the parsed in NPC belongs to the group
	bool inGroup(std::shared_ptr<NPC> npc);

	int GetRandomNumber();

	/// Template methods to be inherited by child classes, these are the core classes for simulating conversation
	virtual void simulateConversation(SDL_Renderer* renderer, bool time, std::string boredomLevel, TTF_Font* font);
	virtual bool evaluateSpeaker();
	virtual void setSpeaker(std::string boredomLevel);

	/// Return the list of NPCs
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

