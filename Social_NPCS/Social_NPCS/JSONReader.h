#pragma once
#include <string>
#include <json\json.h>
#include <fstream>

class JSONReader
{
public:
	JSONReader(std::string fName);

	std::string getFileName();
	void setFileName(std::string fName);

	std::ifstream ReadJsonFile();

private:
	std::string fileName;
};

