#pragma once
#include <memory>
#include <math.h>

#include "Sprite.h"

#define WORLD_SIZE = 800;
class Node//: public Sprite
{
public:
	Node();
	Node(int x, int y, std::shared_ptr<Node> = nullptr);

	int getX();
	void setX(int x);

	int getY();
	void setY(int y);

	int getG();
	void setG(int g);

	int getH();
	void setH(int h);

	int getID();
	void setID();

	std::shared_ptr<Node> getParent();
	void setParent(std::shared_ptr<Node> parent);

	float getF();
	float manHattanDistance(std::shared_ptr<Node> nodeEnd);
private:
	std::pair<int, int> NodeXY;
	std::shared_ptr<Node> parentNode;

	int id;

	float G;
	float H;
};

