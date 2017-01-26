// Social_NPCS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PythonHandler.h"
#include "GroupPopulator.h"
#include "JSONReader.h"
#include "SDLWindow.h"
#include "NPC_Group.h"
#include "TextBox.h"
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
	LoadTexture textureLoader;

	Topic tp = grp.getTopics()[0];
	if (!window.init())
	{
		printf("Failed to initialise!\n");
	}
	else
	{
		bool quit = false;
		Sprite npc(window.getScreenWidth()/2, window.getScreenHeight()/2);
		Sprite npc2((window.getScreenWidth() / 2) + 32, (window.getScreenHeight() / 2 )+ 32);

		NPC_Group group1(window.getScreenWidth()/2, window.getScreenHeight()/2, 6);
		SDL_Event e;
		SDL_Renderer* renderer = window.getRenderer();
		
		TextBox tBox;

		tBox.loadMedia(renderer, "TextBox.png");
		tBox.loadText(renderer, tp.getComments()[0].getBody());

		group1.createGroup(renderer);

		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);
			
			group1.renderGroup(renderer);
			tBox.render(renderer);
			tBox.renderComment(renderer, window.getScreenWidth()/2,window.getScreenHeight()/2);
			SDL_RenderPresent(renderer);
		}

	}
    return 0;
}

