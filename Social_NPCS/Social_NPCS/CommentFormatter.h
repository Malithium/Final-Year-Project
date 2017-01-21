#pragma once
#include <vector>
#include <string>
//#include <algorithm>
#include "Comment.h"
class CommentFormatter
{
public:
	CommentFormatter();
	std::vector<Comment> sortCommentList(Comment com, std::vector<Comment> coms, std::vector<Comment> nComs, int maximum);
	bool contains_id(const std::string& parent_id, const std::string& id);

};

