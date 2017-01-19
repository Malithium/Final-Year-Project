#pragma once
#include "Topic.h"
class Group
{
public:
	Group(std::string nId, std::vector<Topic> nTopics);

	std::string getId();
	std::vector<Topic> getTopics();

	void setId(std::string nId);
	void setTopics(std::vector<Topic> nTopics);

private:
	std::string id;
	std::vector<Topic> topics;
};

