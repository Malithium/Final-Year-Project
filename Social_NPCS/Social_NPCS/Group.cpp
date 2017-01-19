#include "Group.h"

Group::Group(std::string nId, std::vector<Topic> nTopics)
{
	setId(nId);
	setTopics(nTopics);
}

std::string Group::getId()
{
	return id;
}

std::vector<Topic> Group::getTopics()
{
	return topics;
}

void Group::setId(std::string nId)
{
	id = nId;
}

void Group::setTopics(std::vector<Topic> nTopics)
{
	topics = nTopics;
}