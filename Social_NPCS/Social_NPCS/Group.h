#pragma once
#include "Topic.h"
/**
*  Model representation for the Group object within the program
*/
class Group
{
public:
	Group();
	Group(std::string nId, std::vector<Topic> nTopics);

	std::string getId();
	std::vector<Topic> getTopics();

	void setId(std::string nId);
	void setTopics(std::vector<Topic> nTopics);
	friend bool operator== (const Group &c1, const Group &c2);
private:
	std::string id;
	std::vector<Topic> topics;
};

