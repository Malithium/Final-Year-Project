// Social_NPCS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PythonHandler.h"
#include "GroupPopulator.h"
#include "JSONReader.h"
#include <iostream>

int main()
{
	PythonHandler pHandler("comments", "getComments");
	pHandler.callPythonModule();

	JSONReader reader("data.json");
	GroupPopulator populator(reader.ReadJsonFile());
	Group grp = populator.PopulateGroup();

    return 0;
}

