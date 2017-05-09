#pragma once
#include "TextBox.h"
#include "Node.h"

/**
* NPC class inherits from sprite class, uses the textbox class in conjunction with it's base rendering methods for the NPC sprite.
* holds all the actions a NPC can perform within the application.
*/
class NPC: public Sprite
{
public:
	NPC(std::string tBoxSprite, std::string NPCSprite, std::string text, SDL_Renderer* renderer, int x, int y);
	
	/// Breaks up parsed in text into a chunked comment
	void prepareComment(std::string txt, TTF_Font* font);

	/// Loads the NPCs comment into the textbox
	void LoadComment(SDL_Renderer* renderer, int i, TTF_Font* font);

	/// Renders the NPCs comment
	void renderComment(SDL_Renderer* renderer);

	/// Loads the NPCs TextBox
	void LoadBox(SDL_Renderer* renderer);

	/// Renders the NPCs TextBox
	void renderBox(SDL_Renderer* renderer);

	/// Frees up the memory space the textbox is occupying
	void freeBox();

	/// returns the number of line being rendered to the screen
	int getLinesToRender();

	void applyEmotionLevel(float polarity);

	/// Evaluates the emotional level of the NPC
	void evaluateEmotionLevel();

	/// Handles the NPCs movement
	void move();

	void setID(int i);
	int getID();

	int getGroupID();
	void setGroupID(int id);

	int getCurrentLine();
	void setCurrentLine(int id);

	bool getSpeaking();
	void setSpeaking(bool val);

	float getEmotionLevel();

	bool getIdle();
	void setIdle(bool nIdle);

	bool getMoving();
	void setMoving(bool move);

	bool getReading();
	void setReading(bool read);

	int getBoredom();
	void setBoredom(int lvl);

	std::string getCurrentUser();
	void setCurrentUser(std::string user);

	std::vector<std::shared_ptr<Node>> NPC::getPath();
	void NPC::setPath(std::vector<std::shared_ptr<Node>> newPath);

	std::string getText();
	void setText(std::string t);

	std::pair<int, int> getEndGoal();
	void setEndGoal(std::pair<int, int> newGoal);

	friend bool operator== (const NPC &c1, const NPC &c2);
private:
	int id;
	int groupID;
	int currentLine;
	int boredLvl;

	std::string currentUser = "";
	std::string text;
	TextBox speech;

	std::vector<std::shared_ptr<Node>> path;
	std::pair<int, int> endGoal;

	bool speaking = false;
	bool reading = false;
	bool idle = false;
	bool moving = false;

	float emotionLevels = 0.0f;
};

