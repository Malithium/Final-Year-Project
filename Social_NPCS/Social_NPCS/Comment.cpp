#include "Comment.h"

Comment::Comment(std::string nBody, std::string nId, std::string nP_Id, bool nReply, float nPolar): body(nBody), id(nId), parent_id(nP_Id), reply(nReply), polarity(nPolar){}

std::string Comment::getBody()
{
	return body;
}

std::string Comment::getId()
{
	return id;
}

std::string Comment::getParentId()
{
	return parent_id;
}

bool Comment::getReply()
{
	return reply;
}

float Comment::getPolarity()
{
	return polarity;
}

void Comment::setBody(std::string nBody)
{
	body = nBody;
}

void Comment::setId(std::string nId) 
{
	id = nId;
}

void Comment::setParentId(std::string nP_Id)
{
	parent_id = nP_Id;
}

void Comment::setReply(bool nReply)
{
	reply = nReply;
}

void Comment::setPolarity(float polar)
{
	polarity = polar;
}

bool operator== (const Comment &c1, const Comment &c2)
{
	return c1.id == c2.id;
}