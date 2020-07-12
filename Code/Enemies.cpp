#include "Enemies.h"
#include "Grid.h"
#include "GUI.h"

Enemies::Enemies(Cell* pos)
{
	PositionCell = pos;
	slowed = false;
}

void Enemies::Move(Grid* pGrid)
{
	if (counter > 0){
		counter--;
	}
	else{
		slowed = false;
	}

	// Check if the Move is Possible (No Obstacles)
	pGrid->MoveCells(PositionCell); // creates random motion is possible
}

void Enemies::setPosition(Cell* pos)
{
	PositionCell = pos;
}

Cell* Enemies::getPosition(){
	return PositionCell;
}

void Enemies::makeSlow(){
	slowed = true;
	counter = 40;
}

bool Enemies::isSlowed(){
	return slowed;
}