// JUST GET THE BLOCK DATA RENDERED AT LEAST
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>

#include "GUI.h"

#include "engine.h"
#include "Object.h"

using namespace std;

int main (int argc, char *argv[]){
	GUI gui;

	//Create array of Objects:
	const int maxObjects{ (gui.numColumns)*(gui.numRows) + 1 };//+1 for player
	Object objects[maxObjects];

	//Initialize the game's data source
	string gameFile = "C:\\Users\Destructicator\Documents\GitHub\quest-1-Ubtono\quest_1\quest_1\Assets\Config\game.txt";
																						
	//Task 2: Load block structure from a file
    int numObjects = loadBlockData(gameFile, objects, gui);
	cout << numObjects;										 //should return 295
	//Task 3: Randomize Samus Sprite Appearance //INFINITE LOOP
	numObjects++;
	Object player = objects[maxObjects - 1];
	player.type = Type::player;
	cout << getMaxYOfBlock(objects[0], objects, numObjects); // should return 

	randomPlayerData(numObjects, objects, gui);
	
	bool quit = false;
	while (quit == false) {
		//GUI waits for mouse events
		while (gui.observeEvent()) {
			//GUI transmits quit event
			if (gui.quitGame()) {
				quit=true;
			}
		}
        gui.displayGameState(numObjects, objects);
	}

	cout << numObjects;
	return 0;
}
