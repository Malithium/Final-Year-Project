#include "Group.h"

Group::Group(){}

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

bool operator== (const Group &t1, const Group &t2)
{
	return  (t1.id == t2.id) && (t1.topics == t2.topics);
}