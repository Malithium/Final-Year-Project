#pragma once
#include "Comment.h"
/**
* Model representation for the comment object within the program
*/
class Topic
{
public:
	Topic(std::string nId, std::string nTopic, std::vector<Comment> nComments);
	std::string getId();
	std::string getTopic();
	std::vector<Comment> getComments();

	void setId(std::string nId);
	void setTopic(std::string nTopic);
	void setComments(std::vector<Comment> nComments);
private:
	std::string id;
	std::string topic;
	std::vector<Comment> comments;
};

