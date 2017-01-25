// Social_NPCS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PythonHandler.h"
#include "GroupPopulator.h"
#include "JSONReader.h"
#include "SDLWindow.h"
#include <SDL.h>
#include <stdio.h>

#include <iostream>

int main(int argc, char* args[])
{
	PythonHandler pHandler("comments", "getComments");
	pHandler.callPythonModule();

	JSONReader reader("data.json");
	GroupPopulator populator(reader.ReadJsonFile());
	Group grp = populator.PopulateGroup();

	SDLWindow window("Social NPC's", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

	if (!window.init())
	{
		printf("Failed to initialise!\n");
	}
	else
	{
		bool quit = false;

		SDL_Event e;
		
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
			SDL_UpdateWindowSurface(window.getWindow());
		}

	}
    return 0;
}

