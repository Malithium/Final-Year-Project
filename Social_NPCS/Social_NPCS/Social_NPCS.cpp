// Social_NPCS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PythonHandler.h"
#include "GroupPopulator.h"
#include "JSONReader.h"
#include "ResourceData.h"
#include "SDLWindow.h"
#include "NPC_Group.h"
#include "TextBox.h"

int main(int argc, char* args[])
{
	int lastTime = 0, currentTime;

	//Load in our resourceData
	JSONReader resourceReader("ResourceData.json");
	JSONReader reader("data.json");
	ResourceData rData(resourceReader.ReadJsonFile());

	//call the python module to get reddit comments
	std::string pFile = rData.readData("Python_File");
	std::string pMod = rData.readData("Python_Module");
	PythonHandler pHandler(rData.readData("Python_File"), rData.readData("Python_Module"));
	pHandler.callPythonModule();

	//populate the group object with the data from the generated JSON file
	GroupPopulator populator(reader.ReadJsonFile());
	Group grp = populator.PopulateGroup();

	//define the game window
	SDLWindow window("Social NPC's", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

	//initialise the game window
	if (!window.init())
	{
		printf("Failed to initialise!\n");
	}
	else
	{
		bool quit = false;
		
		SDL_Event e;
		SDL_Renderer* renderer = window.getRenderer();

		NPC_Group group1(window.getScreenWidth() / 2, window.getScreenHeight() / 2, 4, rData.readData("TextBox_Sprite"), rData.readData("NPC_Sprite"), renderer, grp.getTopics()[0]);
		NPC_Group group2(window.getScreenWidth()-180, window.getScreenHeight()-180, 5, rData.readData("TextBox_Sprite"), rData.readData("NPC_Sprite"), renderer, grp.getTopics()[1]);
		NPC_Group group3(180, 180, 6, rData.readData("TextBox_Sprite"), rData.readData("NPC_Sprite"), renderer, grp.getTopics()[2]);
		NPC_Group group4(window.getScreenWidth() -180, 180, 2, rData.readData("TextBox_Sprite"), rData.readData("NPC_Sprite"), renderer, grp.getTopics()[3]);
		NPC_Group group5(180, window.getScreenHeight() - 180, 3, rData.readData("TextBox_Sprite"), rData.readData("NPC_Sprite"), renderer, grp.getTopics()[4]);

		//Open up the font to be used in the application
		TTF_Font* font;
		font = TTF_OpenFont(rData.readData("Font_File").c_str(), atoi(rData.readData("Font_Size").c_str()));
		Sprite colorTest("NPC.png", renderer, 100, 100);
		int i = 0;
		bool time = true;

		while (!quit) {
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
			//start tracking the time that has passed since the program started
			currentTime = SDL_GetTicks();

			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);
			/*
			if (currentTime > lastTime + 3000)
			{
				time = true;
				lastTime = currentTime;
			}
			else
			{
				time = false;
			}
			*/
			group1.LoadNPCs(renderer);
			group1.ConversationSimulation(renderer, time, font);
			group1.renderConversation(renderer);

			group2.LoadNPCs(renderer);
			group2.ConversationSimulation(renderer, time, font);
			group2.renderConversation(renderer);

			group3.LoadNPCs(renderer);
			group3.ConversationSimulation(renderer, time, font);
			group3.renderConversation(renderer);

			group4.LoadNPCs(renderer);
			group4.ConversationSimulation(renderer, time, font);
			group4.renderConversation(renderer);

			group5.LoadNPCs(renderer);
			group5.ConversationSimulation(renderer, time, font);
			group5.renderConversation(renderer);

			SDL_RenderPresent(renderer);
		}
		//close our font file
		TTF_CloseFont(font);
	}
    return 0;
}

