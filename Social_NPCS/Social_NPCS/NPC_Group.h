#pragma once
#include <vector>
#include "Sprite.h"
class NPC_Group
{
public:
	NPC_Group(int x, int y, int size);

	std::vector<Sprite> getNPCList();

	void createGroup(SDL_Renderer* renderer);
	void renderGroup(SDL_Renderer* renderer);
	void LoadGroup(SDL_Renderer* renderer);
	void populateVector();
private:
	std::vector<Sprite> NPCs;

	int GroupX;
	int GroupY;
	int GroupSize;
};

