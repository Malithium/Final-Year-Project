#include "Node.h"



Node::Node()
{
}

Node::Node(int x, int y)//: Sprite(filename, renderer, x, y)
{
	NodeXY.first = x;
	NodeXY.second = y;
}

int Node::getX()
{
	return NodeXY.first;
}

void Node::setX(int nX)
{
	NodeXY.first = nX;
}

int Node::getY()
{
	return NodeXY.second;
}

void Node::setY(int nY)
{
	NodeXY.second = nY;
}