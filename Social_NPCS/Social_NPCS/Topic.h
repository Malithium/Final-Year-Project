#pragma once
#include "Comment.h"
/**
* Model representation for the comment object within the program
*/
class Topic
{
public:
	Topic();
	Topic(std::string nId, std::string nTopic, std::vector<Comment> nComments);
	std::string getId();
	std::string getTopic();
	std::vector<Comment> getComments();

	void setId(std::string nId);
	void setTopic(std::string nTopic);
	void setComments(std::vector<Comment> nComments);
	friend bool operator== (const Topic &c1, const Topic &c2);
private:
	std::string id;
	std::string topic;
	std::vector<Comment> comments;
};

