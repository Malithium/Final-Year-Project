#include "Node.h"

Node::Node(){}

Node::Node(int x, int y, std::shared_ptr<Node> node) : G(0), H(0)
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

float Node::getF()
{
	return G + H;
}

std::shared_ptr<Node> Node::getParent()
{
	return parentNode;
}

void Node::setParent(std::shared_ptr<Node> nParent)
{
	parentNode = nParent;
}

float Node::manHattanDistance(std::shared_ptr<Node> endNode)
{
	float x = (float)(fabs(this->getX() - endNode->getX()));
	float y = (float)(fabs(this->getY() - endNode->getY()));

	return x + y;
}