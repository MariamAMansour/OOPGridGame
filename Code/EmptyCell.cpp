#include "EmptyCell.h"
#include "Player.h"


EmptyCell::EmptyCell(int r, int c):Cell(r,c)
{
	ImagePath = "images\\Cells\\Empty Cell.jpg";
	Celltype = "EmptyCell";
}


EmptyCell::~EmptyCell(void)
{
}



bool EmptyCell::ActOn(Player* p)
{
	//Empty cell takes no action on player
	//it returns true as it is NOT an obstacle cell
	return true;
}


bool EmptyCell::walkthrough(){
	return true;
}

string EmptyCell::Message(){
	return "  ";
}

