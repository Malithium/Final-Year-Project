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
	void prepareComment(std::string txt, TTF_Font* font);
	void LoadComment(SDL_Renderer* renderer, int i, TTF_Font* font);

	void LoadBox(SDL_Renderer* renderer);
	void renderBox(SDL_Renderer* renderer);

	void renderComment(SDL_Renderer* renderer);

	void freeBox();

	bool getSpeaking();
	void setSpeaking(bool val);

	void setBoredom(int bored);
	int getBoredom();

	float getEmotionLevel();
	void applyEmotionLevel(float polarity);
	void evaluateEmotionLevel();

	bool getReadingTopic();
	void setReadingTopic(bool val);

	bool getIdle();
	void setIdle(bool nIdle);

	SDL_Rect getBBox();
	void setBBox(int x, int y, int width, int height);

	std::vector<std::shared_ptr<Node>> NPC::getPath();
	void NPC::setPath(std::vector<std::shared_ptr<Node>> newPath);

	int getLinesToRender();

	std::string getText();
	void setText(std::string t);

	std::pair<int, int> getEndGoal();
	void setEndGoal(std::pair<int, int> newGoal);

private:
	TextBox speech;
	std::vector<std::shared_ptr<Node>> path;

	std::string text;
	bool speaking = false;
	bool readingTopic = false;
	bool idle = false;
	std::pair<int, int> endGoal;

	float emotionLevels = 0.0f;
	int boredom = 0;

	SDL_Rect colliderBox;
};

