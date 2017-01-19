#include "JSONReader.h"

JSONReader::JSONReader(std::string fName)
{
	setFileName(fName);
}

std::string JSONReader::getFileName()
{
	return fileName;
}

void JSONReader::setFileName(std::string fName)
{
	fileName = fName;
}

std::ifstream JSONReader::ReadJsonFile()
{
	return std::ifstream(fileName, std::ifstream::binary);
}
