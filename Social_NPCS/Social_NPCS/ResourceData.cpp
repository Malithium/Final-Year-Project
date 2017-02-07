#include "ResourceData.h"



ResourceData::ResourceData(std::ifstream file)
{
	file >> root;
}

std::string ResourceData::readData(std::string key)
{
	return root[key].asString();
}