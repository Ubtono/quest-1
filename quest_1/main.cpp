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
	string gameFile = "./Assets/Config/game.txt";
																						
	//Task 2: Load block structure from a file
    int numObjects = loadBlockData(gameFile, objects, gui);
	cout << numObjects;										 //should return 295
	//Task 3: Randomize Samus Sprite Appearance //INFINITE LOOP
	cout << "second object width and height: " << objects[1].dimensions.width << "x" << objects[1].dimensions.height;
	Object player = objects[numObjects - 1];
	//player.type = Type::player;
	//cout << getMaxYOfBlock(objects[0], objects, numObjects); // should return 

	//randomPlayerData(numObjects, objects, gui);
	
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
