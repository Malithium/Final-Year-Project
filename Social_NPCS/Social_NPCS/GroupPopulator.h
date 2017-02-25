#pragma once
#include <json\json.h>
#include <fstream>
#include "Group.h"
#include "CommentFormatter.h"

/**
* Populates the group object with data parsed into the contructor
*/
class GroupPopulator
{
public:
	GroupPopulator(std::ifstream file);
	GroupPopulator();
	Group PopulateGroup();

private:
	Json::Value root;
};

