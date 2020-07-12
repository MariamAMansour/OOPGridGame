#include "Cell.h"
#include "Player.h"
#include "GoalCell.h"

using namespace std;

GoalCell::GoalCell(int r, int c):
Cell(r, c){
	ImagePath = "images\\cells\\Goal Cell.jpg";
	Celltype = "GoalCell";
}

GoalCell::~GoalCell(void)
{
}

bool GoalCell::ActOn(Player* p){
	p->setWon(true);
	return false;
}

bool GoalCell::walkthrough(){
	return false;
}

string GoalCell::Message(){
	return "  ";
}