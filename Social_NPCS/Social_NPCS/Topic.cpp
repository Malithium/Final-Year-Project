#include "Topic.h"



Topic::Topic(std::string nId, std::string nTopic, std::vector<Comment> nComments)
{
	setId(nId);
	setTopic(nTopic);
	setComments(nComments);
}

std::string Topic::getId()
{
	return id;
}

std::string Topic::getTopic()
{
	return topic;
}

std::vector<Comment> Topic::getComments()
{
	return comments;
}

void Topic::setId(std::string nId)
{
	id = nId;
}

void Topic::setTopic(std::string nTopic)
{
	topic = nTopic;
}

void Topic::setComments(std::vector<Comment> nComments)
{
	comments = nComments;
}