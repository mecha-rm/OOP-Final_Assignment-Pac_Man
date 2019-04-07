/*
* Project: Object Oriented Programming - Final Project - PAC-MAN
* Date: 04/06/2019

* Group Members: Assignment Group 6
	- Caleb Birnie (100699828)
	- Nathan Tuck (100708651)
	- Roderick “R.J.” Montague (100701758)
	- Ryan Burton (100707511)
	- Tavis East (100702011)

*/
// creates a maze
#include "Maze.h"

#include <iostream>
#include <fstream>
#include <algorithm>

const float Maze::SQUARE_SIZE = 32.0F;

Maze::Maze() : Maze(0) {}

// constructor
Maze::Maze(unsigned int level)
{
	setLevel(level);
}

// changes the level
void Maze::setLevel(unsigned int level)
{
	// loads in a level file.
	switch (level)
	{
	case 1:
		loadData("levels/level_01.txt");
		break;
	case 2:
		loadData("levels/level_02.txt");
		break;
	}
}

// loads the level data
void Maze::loadData(std::string fileName)
{
	std::ifstream file(fileName, std::ios::in); // opens up the file
	std::string str;

	int rowNum = 0;
	int colNum = 0;
	bool added = false; // used to see if something was added or not.

	bool hasPen = false; // used to check if there's a ghost pen.
	int penRow = 0; // the row the pen is in
	int penCol = 0; // the column the pen is in
	
	try
	{
		if (!file)
			throw "Error accessing file. Default area loaded.";
	}
	catch (const char * ex)
	{
		std::cout << ex << std::endl;
		return; // leaves default values in maze.
	}


	rowNum = 0;
	colNum = 0;

	while (file.is_open() && !file.eof())
	{
		std::getline(file, str); // gets a line of the file.

		for (int k = 0; k < str.length(); k++)
		{
			if (ustd::isInt(str.substr(k, 1))) // if the character is an integer.
			{
				map[rowNum][colNum] = std::stoi(str.substr(k, 1)); // gets hte string as an integer.
				colNum++;

				if (colNum >= COL_MAX) // if all columns for the row have been filled.
					break;

				added = true; // knows that something has been added to the row
			}
		}

		str.clear();

		if(added) // if a block has been added to the row, then move onto the next.
			rowNum++;

		if (rowNum >= ROW_MAX) // if all rows have been filled, information from the file is no longer read.
			break;

		added = false;
		colNum = 0;
	}

	rowNum = 0;
	colNum = 0;
	
	file.close();

	//// goes through and deletes all instances of the ghost pen.
	//for (int i = 0; i < ROW_MAX; i++) // going through each row
	//{
	//	for (int j = 0; j < COL_MAX; j++) // going through each column
	//	{
	//		if (hasPen == true) // if one pen has already been found
	//		{
	//			map[i][j] = 0;
	//			continue;
	//		}


	//		for (int row = 2; row >= -2; row++) // clears out 2 rows above and below of the pen to make room
	//		{
	//			for (int col = 2; col >= -2; col++) // clears out 2 columns left and right the pen
	//			{
	//				// if the index goes beyond the indexes of the array, the loop continues.
	//				if (i + col >= COL_MAX || i + col <= 0 || j + row >= ROW_MAX || j + row <= 0)
	//					continue;

	//				map[i + col][j + row] = 0; // sets the index to 0.
	//				hasPen = true; // the ghostpen has been found.

	//			}
	//		}
	//	}
	//}
	

}

// gets the player's spawn point in the maze.
Vec2 Maze::getPlayerSpawn() const { return plyrSpawn; }

// generates the maze graphics
std::vector<entity::Entity *> Maze::generate()
{
	std::vector<entity::Entity *> gameObjects; // a vector of game objects
	bool added = false; // becomes true if something was just added.
	Vec2 position = Vec2(0.0F, 0.0F);


	float tempWidth = 0.0F; // momentarily saves the height to check for the maze size
	float tempHeight = 0.0F; // momentarily saves the width to check for the maze size
	

	for (int i = 0; i < ROW_MAX; i++) // going through each row
	{
		for (int j = 0; j < COL_MAX; j++) // going through each column
		{
			position = Vec2(j * SQUARE_SIZE + SQUARE_SIZE / 2.0F, COL_MAX * SQUARE_SIZE - i * SQUARE_SIZE + SQUARE_SIZE / 2.0F);

			/*
			 * The maze map. The position is set opposite to how it appears in the array (e.g. row(0) is the top of the map, not the bottom.
				* 0 - empty
				* 1 - block 
				* 2 - pacdot ~the things pacman collects
				* 3 - power pellet
				* 4 - ghost pen ~ the ghost spawns on top of this area.
				* 5 - player ~ sets their position in the maze
				* 6 - red
				* 7 - pink
				* 8 - blue
				* 9 - orange
			*/
			switch (map[i][j])
			{
			case 1: // block
				gameObjects.push_back(new entity::Block()); // sets hte position of the block
				added = true;
				break;

			case 2: // pac-dot
				gameObjects.push_back(new entity::Dot());
				added = true;
				break;

			case 3: // power pellet
				gameObjects.push_back(new entity::Pellet());
				added = true;
				break;

			case 4: // ghost pen, which is (5 X 4 squares)
				// Vec2 pos;

				// top
				gameObjects.push_back(new entity::Block(position + Vec2(SQUARE_SIZE * -2, SQUARE_SIZE * 2)));
				gameObjects.push_back(new entity::Block(position + Vec2(SQUARE_SIZE * -1, SQUARE_SIZE * 2)));
				gameObjects.push_back(new entity::Block(position + Vec2(SQUARE_SIZE * 0, SQUARE_SIZE * 2)));
				gameObjects.push_back(new entity::Block(position + Vec2(SQUARE_SIZE * 1, SQUARE_SIZE * 2)));
				gameObjects.push_back(new entity::Block(position + Vec2(SQUARE_SIZE * 2, SQUARE_SIZE * 2)));

				// bottom
				gameObjects.push_back(new entity::Block(position + Vec2(SQUARE_SIZE * -2, SQUARE_SIZE * -2)));
				gameObjects.push_back(new entity::Block(position + Vec2(SQUARE_SIZE * -1, SQUARE_SIZE * -2)));
				gameObjects.push_back(new entity::Block(position + Vec2(SQUARE_SIZE * 0, SQUARE_SIZE * -2)));
				gameObjects.push_back(new entity::Block(position + Vec2(SQUARE_SIZE * 1, SQUARE_SIZE * -2)));
				gameObjects.push_back(new entity::Block(position + Vec2(SQUARE_SIZE * 2, SQUARE_SIZE * -2)));

				// sides
				gameObjects.push_back(new entity::Block(position + Vec2(SQUARE_SIZE * -2, SQUARE_SIZE * -1)));
				gameObjects.push_back(new entity::Block(position + Vec2(SQUARE_SIZE * -2, SQUARE_SIZE * 0)));
				gameObjects.push_back(new entity::Block(position + Vec2(SQUARE_SIZE * -2, SQUARE_SIZE * 1)));

				gameObjects.push_back(new entity::Block(position + Vec2(SQUARE_SIZE * 2, SQUARE_SIZE * -1)));
				gameObjects.push_back(new entity::Block(position + Vec2(SQUARE_SIZE * 2, SQUARE_SIZE * 0)));
				gameObjects.push_back(new entity::Block(position + Vec2(SQUARE_SIZE * 2, SQUARE_SIZE * 1)));

				// making the ghosts

				gameObjects.push_back(new entity::Enemy(1));
				gameObjects.at(gameObjects.size() - 1)->setPosition(position.x, position.y + SQUARE_SIZE * 3.0F);
				gameObjects.push_back(new entity::Enemy(2));
				gameObjects.at(gameObjects.size() - 1)->setPosition(position.x, position.y);
				gameObjects.push_back(new entity::Enemy(3));
				gameObjects.at(gameObjects.size() - 1)->setPosition(position.x - SQUARE_SIZE, position.y);
				gameObjects.push_back(new entity::Enemy(4));
				gameObjects.at(gameObjects.size() - 1)->setPosition(position.x + SQUARE_SIZE, position.y);



				// gameObjects.push_back(new entity::Block((Vec2(j * SQUARE_SIZE + SQUARE_SIZE / 2.0F, COL_MAX * SQUARE_SIZE - i * SQUARE_SIZE + SQUARE_SIZE / 2.0F)));

				break;

			case 5: // player position; uses the last instance of this number, even though there should only be one.
				plyrSpawn = (Vec2(j * SQUARE_SIZE + SQUARE_SIZE / 2.0F, COL_MAX * SQUARE_SIZE - i * SQUARE_SIZE + SQUARE_SIZE / 2.0F));
			
				break;

			case 6: // red ghost
				gameObjects.push_back(new entity::Enemy(1));
				added = true;
				break;

			case 7: // pink ghost
				gameObjects.push_back(new entity::Enemy(2));
				added = true;
				break;

			case 8: // blue ghost
				gameObjects.push_back(new entity::Enemy(3));
				added = true;
				break;

			case 9: // orange ghost
				gameObjects.push_back(new entity::Enemy(4));
				added = true;
				break;

			}



			if (added) // if the item was added, its position is set
			{
				// gameObjects.at(gameObjects.size() - 1)->setPosition(Vec2(j * SQUARE_SIZE + SQUARE_SIZE / 2.0F, COL_MAX * SQUARE_SIZE - i * SQUARE_SIZE + SQUARE_SIZE / 2.0F));
				gameObjects.at(gameObjects.size() - 1)->setPosition(position);
				gameObjects.at(gameObjects.size() - 1)->setSpawnPosition(gameObjects.at(gameObjects.size() - 1)->getPosition());

				// gets the potential new height/width of the maze.
				tempWidth = j * SQUARE_SIZE + SQUARE_SIZE;
				tempHeight = i * SQUARE_SIZE + SQUARE_SIZE;

				if (tempWidth > width) // new width
					width = tempWidth;
				
				if (tempHeight > height) // new height
					height = tempHeight;

			}

			added = false; // reset for next loop
			tempWidth = 0.0F;
			tempHeight = 0.0F;

		}
	}

	// sets the size of the maze
	entity::Entity::winSize = Size(width, height);

	return gameObjects;
}


