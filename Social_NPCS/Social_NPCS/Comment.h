#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

/**
* Model representation for the comment object within the program
*/
class Comment
{
public:
	Comment(std::string nBody, std::string nId, std::string nP_Id, bool nReply, float polar, std::string username);


	std::string getBody();
	std::string getId();
	std::string getParentId();
	std::string getUserName();
	bool getReply();
	float getPolarity();

	void setBody(std::string nBody);
	void setId(std::string nId);
	void setParentId(std::string pId);
	void setUserName(std::string name);
	void setReply(bool rep);
	void setPolarity(float polar);

	/// Custom comparison operator
	friend bool operator== (const Comment &c1, const Comment &c2);

private:
	std::string n;
	std::string body;
	std::string id;
	std::string parent_id;
	std::string userName;
	float polarity;
	bool reply;
};
