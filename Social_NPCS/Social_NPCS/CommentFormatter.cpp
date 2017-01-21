#include "CommentFormatter.h"

CommentFormatter::CommentFormatter()
{
}

/*
This function recursively calls itself, it sorts a list of Comment's so that a comment is followed by a reply to it if it exists,
reply's can also have reply's as well so we do not distinguish between comment or reply during this process.
*/
std::vector<Comment> CommentFormatter::sortCommentList(Comment com, std::vector<Comment> coms, std::vector<Comment> nComs, int maximum)
{
	//we only want to do this when nComs is less than the maximum given value
	if (nComs.size() < maximum) {

		//push back the current comment
		nComs.push_back(com);

		//erase the comment from coms, this is so that we do not go beyond the index range of coms, and to avoid adding duplicates
		coms.erase(std::remove(coms.begin(), coms.end(), com), coms.end());
		for (int i = 0; i < coms.size(); i++)
		{
			//we check to see if a comment contain's the id of com in it's parent_id, if it does, then it is a reply to that comment
			if (contains_id(coms[i].getParentId(), com.getId())) {
				Comment cRep = coms[i];

				//remove the reply from the comments array
				coms.erase(std::remove(coms.begin(), coms.end(), coms[i]), coms.end());

				//parse the reply into this function along with our current value's, this is so that we can find any reply's for the reply itself
				nComs = sortCommentList(cRep, coms, nComs, maximum);
			}
		}

		//if the size of com's is not 0, then there are still comments we have not sorted so we call the function again.
		if(coms.size() != 0)
			nComs = sortCommentList(coms[0], coms, nComs, maximum);
	}
	return nComs;
}


/*
This is a custom find for 2 string's the goal is to check if a given id exists within a parent_id
*/
bool CommentFormatter::contains_id(const std::string& parent_id, const std::string& id)
{
	size_t pos = 0;
	while ((pos = parent_id.substr(pos).find(id)) != std::string::npos)
	{
		if (!(isalpha(parent_id[pos - 1])) || !(isalpha(parent_id[pos + id.size() + 1])))
			return true;
	}
	return false;
}
