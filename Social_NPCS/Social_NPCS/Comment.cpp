#include "Comment.h"



Comment::Comment(std::string nBody, std::string nId, std::string nP_Id, bool nReply, std::vector<std::string>replyIds)
{
	setBody(nBody);
	setId(nId);
	setParentId(nP_Id);
	setReply(nReply);
	setReplyIds(replyIds);
}

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

std::vector<std::string> Comment::getReplyIDs()
{
	return reply_IDs;
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

void Comment::setReplyIds(std::vector<std::string> nReplyIds)
{
	reply_IDs = nReplyIds;
}