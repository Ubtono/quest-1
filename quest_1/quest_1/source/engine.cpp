
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
	int numData;
	Object* newObject = new Object();
	for (int rowId = 1; rowId <= p_gui.numRows; rowId++) {
		for (int colId = 1; colId <= p_gui.numColumns; colId++) {
			fs >> numData;
			int blockType = numData + 1;

			if (blockType == 1) {
				newObject->type = Type::none;
				newObject->dimensions.height = 16;
				newObject->dimensions.width = 16;
				p_objects[objectIndex] = *newObject;

				objectIndex += 1;
			}
			else {

				newObject->type = static_cast<Type>(blockType);
				newObject->dimensions.width = p_gui.getObjectDimensions(*newObject).width;
				newObject->position.x = newObject->dimensions.width * colId;
				//std::cout << "X position: " << p_gui.getObjectDimensions(currObject).height << std::endl;
				newObject->dimensions.height = p_gui.getObjectDimensions(*newObject).height;
				newObject->position.y = newObject->dimensions.height * rowId;

				p_objects[objectIndex] = *newObject;

				objectIndex += 1;

			}
		}
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
void randomPlayerData (
    const int p_numObjects,
    Object p_objects[],
    const GUI & p_gui) 
{
	int i{ 0 };
	Object tempplayer = p_objects[i];
	tempplayer.top = false;

	while (!tempplayer.top) {
		for (int colID{ 0 }; colID < p_numObjects; colID++) {
		
				tempplayer.position.x = 8;//rand() % GUI::screenDimensions.width;
				tempplayer.position.y = 8;//rand() % GUI::screenDimensions.height;
				tempplayer.dimensions.height = 120;//getMaxYOfBlock(player, p_objects, p_numObjects);


			for (int rowID{ 0 }; rowID < tempplayer.position.y; rowID++) {
					if (p_objects[rowID].type != Type::none) {
						tempplayer.top = false;
					}
					else {
						tempplayer.top = true;
					}
			}
			
		}
	}
	Object player = tempplayer;
	player.spriteID = rand() % 100;
	player.type = Type::player;
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
