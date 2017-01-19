#pragma once
#include <json\json.h>
#include <fstream>
#include "Group.h"
class GroupPopulator
{
public:
	GroupPopulator(std::ifstream file);
	Group PopulateGroup();
private:
	Json::Value root;
};

