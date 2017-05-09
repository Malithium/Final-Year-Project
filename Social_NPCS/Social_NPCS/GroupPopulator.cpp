#include "GroupPopulator.h"


GroupPopulator::GroupPopulator()
{

}

GroupPopulator::GroupPopulator(std::ifstream file)
{
	file >> root;
}

/**
* access's the read in JSON file to populate our group object
*/
Group GroupPopulator::PopulateGroup()
{
	std::vector<Topic> nTops;
	CommentFormatter cfrm;
	std::vector<Comment> a;

	// access each 'topics' value in the JSON file
	for (const Json::Value& tops : root["topics"])
	{
		std::vector<Comment> nComms;

		// acess each 'comments' value in the JSON file
		for (const Json::Value& comms : tops["comments"])
		{
			Comment com(comms["body"].asString(), comms["id"].asString(), comms["parent_id"].asString(), 
				comms["reply"].asBool(), comms["polarity"].asFloat(), comms["author"].asString());
			nComms.push_back(com);
		}

		// use the comment formatter to format the list, then add it to the topic
		nComms = cfrm.sortCommentList(nComms[0], nComms, a, nComms.size());
		Topic top(tops["id"].asString(), tops["topic"].asString(), nComms);

		// add the topic to the group
		nTops.push_back(top);
	}
	return Group(root["subject"].asString(), nTops);
}