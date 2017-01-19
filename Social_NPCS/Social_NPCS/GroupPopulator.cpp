#include "GroupPopulator.h"



GroupPopulator::GroupPopulator(std::ifstream file)
{
	file >> root;
}

Group GroupPopulator::PopulateGroup()
{
	std::vector<Topic> nTops;
	for (const Json::Value& tops : root["topics"])
	{
		std::vector<Comment> nComms;
		for (const Json::Value& comms : tops["comments"])
		{
			std::vector<std::string> replys;
			Comment com(comms["body"].asString(), comms["id"].asString(), comms["parent_id"].asString(), comms["reply"].asBool(), replys);
			nComms.push_back(com);
		}
		Topic top(tops["id"].asString(), tops["topic"].asString(), nComms);
		nTops.push_back(top);
	}
	return Group(root["subject"].asString(), nTops);
}
