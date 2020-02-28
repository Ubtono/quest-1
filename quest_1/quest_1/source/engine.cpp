
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

/*
position = {
column * p_objects[i].dimensions.width;
rows * p_objects[i].dimensions.height;
*/
int loadBlockData(
	const std::string& p_gameFile,
	Object p_objects[],
	const GUI& p_gui) 
{
	//auto size = p_objects.size();
	fs.open(p_gameFile, std::fstream::in | std::fstream::out);

	int objectIndex = 0;
	int numData = -1;
	Object currObject = p_objects[objectIndex];
	for (int rowId = 0; rowId < 10; rowId++) {
		for (int colId = 0; colId < 10; colId++) {
			fs >> numData;
			currObject.type = static_cast<Type>(numData);
			currObject.position.x = colId * p_gui.getObjectDimensions(currObject).width;
			//std::cout << "X position: " << p_gui.getObjectDimensions(currObject).height << std::endl;
			currObject.position.y = rowId * p_gui.getObjectDimensions(currObject).height;
			
			objectIndex++;
			colId++;
		}
		rowId++;
	}
	return objectIndex;
}

	/*
	int i = 0;
	char numData{ 'c' };
	Object* pntr = new Object();
	for (i; i < size; i++) {
		//std::cout << "End of file not yet reached" << std::endl;
		fs >> numData;
		//How can I access the size of the vector
		Object currObject = p_objects[i];
		currObject.type = static_cast<Type>(numData);
		//i++;
		}
	return i;
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
void randomPlayerData ( //INFINITE LOOP
    const int p_numObjects,
    Object p_objects[],
    const GUI & p_gui) 
{
	Object player;
	while (!player.top) {
		player.position.x = rand() % p_gui.numColumns;
		player.position.y = rand() % p_gui.numRows;
		player.dimensions.height = getMaxYOfBlock(player, p_objects, p_numObjects);
		player.spriteID = rand() % 100;
		
		if (player.type == static_cast<Type>(0)) {
			player.top = true;
		}
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
