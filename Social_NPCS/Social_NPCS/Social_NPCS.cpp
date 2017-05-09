// Social_NPCS.cpp : Defines the entry point for the console application.
//

#include "PythonHandler.h"
#include "GroupPopulator.h"
#include "JSONReader.h"
#include "ResourceData.h"
#include "SDLWindow.h"
#include "Room.h"
#include "TextBox.h"
#include <sys/stat.h>
#include <sys/types.h>

/**
* Entry point of the program
*/
int main(int argc, char* args[])
{
	int lastTime = 0, currentTime;
	struct stat st;


	//Load in our resourceData
	JSONReader resourceReader("ResourceData.json");
	JSONReader reader("data.json");

	int ierr = stat("data.json", &st);
	if (ierr != 0) {
		std::cout << "error";
	}

	time_t date = st.st_mtime;
	time_t base;
	time(&base);

	ResourceData rData(resourceReader.ReadJsonFile());

	//check the timestamp on our data file, if it is less than 24 hours, then dont run the python script
	if (rData.readData("Enable_Python") == "true")
	{
		if ((base - date) >= 60 * 60 * 24)
		{
			//call the python module to get reddit comments
			std::string pFile = rData.readData("Python_File");
			std::string pMod = rData.readData("Python_Module");
			PythonHandler pHandler(rData.readData("Python_File"), rData.readData("Python_Module"));
			pHandler.callPythonModule();
		}
	}

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
		Room room1(5, 180, 180, window.getScreenWidth(), window.getScreenHeight(), rData.readData("NPC_Sprite"), rData.readData("TextBox_Sprite"), renderer, grp);

		//Open up the font to be used in the application
		TTF_Font* font;
		font = TTF_OpenFont(rData.readData("Font_File").c_str(), atoi(rData.readData("Font_Size").c_str()));
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
			
			if (currentTime > lastTime + atoi(rData.readData("Timer_Value").c_str()))
			{
				time = true;
				lastTime = currentTime;
			}
			else
			{
				time = false;
			}

			// Render the NPC sprites to the screen
			room1.LoadNPCs(renderer);

			// Simulate and render the conversation of the NPCs
			room1.LoadConversation(renderer, time, rData.readData("Boredom_Level"), font);

			// Handle the movement of any idle NPCs
			room1.HandleMove(renderer);

			SDL_RenderPresent(renderer);
		}
		//close our font file
		TTF_CloseFont(font);
	}
    return 0;
}

