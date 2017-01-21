#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
class Comment
{
public:
	Comment(std::string nBody, std::string nId, std::string nP_Id, bool nReply);

	std::string getBody();
	std::string getId();
	std::string getParentId();
	bool getReply();

	void setBody(std::string nBody);
	void setId(std::string nId);
	void setParentId(std::string pId);
	void setReply(bool rep);
	friend bool operator== (const Comment &c1, const Comment &c2);
private:
	std::string body;
	std::string id;
	std::string parent_id;
	bool reply;
};

