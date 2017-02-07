#pragma once
#include <json/json.h>
#include <string>
#include <fstream>

class ResourceData
{
public:
	ResourceData(std::ifstream file);

	std::string readData(std::string key);
private:
	Json::Value root;

};

