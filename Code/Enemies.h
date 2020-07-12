#pragma once

#include "Cell.h"
#include "GUI.h"
class Grid;

class Enemies
{
	Cell* PositionCell;
	bool slowed;		//true if enemy is affected by a SlowDownWeapon
	int counter;		//counts the 40 steps of slow movement


public:
	Enemies(); //default constructor
	Enemies(Cell* pos); // Constructor
	
	void setPosition(Cell*);		//changes position of the cell
	Cell* getPosition();			//returns a pointer to the position cell
	void Move(Grid* pGrid); // Moves the cell in a specific direction if possible
	void makeSlow(); //turns Slowed bool to true when player touches it
	bool isSlowed();
};