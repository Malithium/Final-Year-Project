#pragma once
#include <string>
#include <vector>
class Comment
{
public:
	Comment(std::string nBody, std::string nId, std::string nP_Id, bool nReply, std::vector<std::string>replyIds);

	std::string getBody();
	std::string getId();
	std::string getParentId();
	bool getReply();
	std::vector<std::string> getReplyIDs();

	void setBody(std::string nBody);
	void setId(std::string nId);
	void setParentId(std::string pId);
	void setReply(bool rep);
	void setReplyIds(std::vector<std::string> rIds);

private:
	std::string body;
	std::string id;
	std::string parent_id;
	bool reply;
	std::vector<std::string> reply_IDs;
};

