#include "Topic.h"

Topic::Topic()
{

}

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

bool operator== (const Topic &t1, const Topic &t2)
{
	return  (t1.id == t2.id) && (t1.topic == t2.topic) && (t1.comments == t2.comments);
}