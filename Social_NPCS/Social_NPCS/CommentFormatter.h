#pragma once
#include <vector>
#include <string>
#include "Comment.h"

/**
* The comment formatter sorts the a list of comments by comment->reply->reply... 
*/
class CommentFormatter
{
public:
	CommentFormatter();
	std::vector<Comment> sortCommentList(Comment com, std::vector<Comment> coms, std::vector<Comment> nComs, int maximum);
	bool contains_id(const std::string& parent_id, const std::string& id);

};

