#pragma once
#include <memory>
#include "Sprite.h"
class Node//: public Sprite
{
public:
	Node();
	Node(int x, int y);

	int getX();
	void setX(int x);

	int getY();
	void setY(int y);
private:
	std::pair<int, int> NodeXY;
};

