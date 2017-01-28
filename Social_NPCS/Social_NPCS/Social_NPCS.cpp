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

int lastTime = 0, currentTime;

int main(int argc, char* args[])
{
	PythonHandler pHandler("comments", "getComments");
	pHandler.callPythonModule();

	JSONReader reader("data.json");
	GroupPopulator populator(reader.ReadJsonFile());
	Group grp = populator.PopulateGroup();

	SDLWindow window("Social NPC's", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	LoadTexture textureLoader;

	Uint32 startTime = 0;
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

	
		SDL_Event e;
		SDL_Renderer* renderer = window.getRenderer();
		NPC_Group group1(window.getScreenWidth() / 2, window.getScreenHeight() / 2, 6, renderer, grp.getTopics()[0]);
		NPC oneNPC("Textbox.png", "NPC.png", grp.getTopics()[0].getTopic(), renderer, window.getScreenWidth() / 2, window.getScreenHeight() / 2);

		int i = 0;
		bool time = false;
		while (!quit) {
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
			currentTime = SDL_GetTicks();
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);
			/*
			if (i == 0)
			{
				oneNPC.LoadComment(renderer, i);
				i++;
			}
			if (currentTime > lastTime + 3000)
			{
				if (i > oneNPC.getLinesToRender())
					i = 0;
				oneNPC.LoadComment(renderer, i);
				lastTime = currentTime;
				i++;
			}
			*/

			group1.LoadNPCs(renderer);
			group1.ConversationSimulation(renderer, time);
			//oneNPC.render(renderer);
			//oneNPC.renderBox(renderer);
			//oneNPC.renderComment(renderer);
			if (currentTime > lastTime + 3000)
			{
				time = true;
				lastTime = currentTime;
			}
			else
			{
				time = false;
			}
			group1.renderConversation(renderer);
			SDL_RenderPresent(renderer);
			//std::cout << "Time: " << startTime << std::endl;
		}
	}
    return 0;
}

