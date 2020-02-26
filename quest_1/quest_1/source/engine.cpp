
#include "engine.h"

// stdlib
#include <iostream>
#include <fstream>
#include <random>
// local
#include "Object.h"
#include "GUI.h"
std::ifstream fs;

/*
	-- loadBlockData   --
	Parameters:
		p_gameFile : A string representing the location of the game data file
		p_objects  : An array of default-constructed objects, each element
					 needs to be updated to with the correct information from
					 the data file
		p_gui      : A reference to the GUI Object if you need it

	Return: the number of objects read from the data file

	loadBlockData will read the p_gameFile and update the objects in
	p_objects with the appropriate data.
*/
int loadBlockData(
	const std::string& p_gameFile,
	Object p_objects[],
	const GUI& p_gui)
{
	fs.open(p_gameFile, std::fstream::in | std::fstream::out);
	int index = 0;
	while (fs) {
		Object currObject = p_objects[index];
		int numData{ -1 };
		fs >> numData;
		currObject.spriteID = numData;
		currObject.type = static_cast<Type>(numData);

		index++;
	}


	return index + 1;
}
	/*
	char c;
	int numObjects{ 0 };
	if (fs.is_open()) {
		int col;
		int row{ 0 };
		while (!fs.eof()) {
			for (col = 0; col < p_gui.numColumns; col++) {
				fs >> c;

				if (c == 1) {
					p_objects[numObjects].top = true;
				}
				else {
					p_objects[numObjects].top = false;
				}
				p_objects[numObjects].type = static_cast<Type>(c);
				p_objects[numObjects].position.x = col;
				p_objects[numObjects].position.y = row;


				//p_objects[numObjects].dimensions = new Dimensions();
				//p_objects[numObjects].dimensions->getObjectDimensions(p_objects[numObjects]);

				p_objects[numObjects].dimensions = GUI::getObjectDimensions(p_objects[numObjects]);

				numObjects++;
			}
			row++;			
			//p_objects[numObjects].dimensions = { row, col };
		}
	} 

    return numObjects;	
}
*/
/*
	-- randomPlayerData   --
	Parameters:
		p_numObjects : The total number of objects in p_objects
		p_objects    : An array of almost all fully-constructed objects
		p_gui      : A reference to the GUI Object if you need it

	This function needs to modify the player object and assign them random values.
	Player
		xPosition needs to be random
		spriteID needs to be random
		yPosition needs to be physically correct
			The player cannot be in the air for instance
			The player cannot be underground
*/
void randomPlayerData (
    const int p_numObjects,
    Object p_objects[],
    const GUI & p_gui) 
{
	Object player = p_objects[0];
	while (!player.top) {
		player.position.x = rand() % p_gui.numColumns;
		player.position.y = getMaxYOfBlock(player, p_objects, p_numObjects);
		player.spriteID = rand() % 100;
	}
}

/*
	-- getMaxYOfBlock --
	Parameters
		player  - A read-only reference to the player object
		objects - A list of read-only objects
		numObjects - The number of objects

	Return: The height that the player needs to be at to be physically accurate
*/
int getMaxYOfBlock (
    const Object& player,
    const Object objects[],
    int numObjects) 
{
	return player.position.y;
} 
