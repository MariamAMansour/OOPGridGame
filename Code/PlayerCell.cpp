#include "PlayerCell.h"
#include "Player.h"


PlayerCell::PlayerCell(int row, int col):Cell(row,col)
{
	ImagePath = "images\\Cells\\player.jpg";
	Celltype = "PlayerCell";
}


PlayerCell::~PlayerCell()
{
}

bool PlayerCell::ActOn(Player* p)
{
	//Empty cell takes no action on player
	//it returns true as it is NOT an obstacle cell
	return true;
}

bool PlayerCell::walkthrough(){
	return false;
}


