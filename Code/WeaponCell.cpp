#include "WeaponCell.h"
#include "Player.h"
#include "Cell.h"


WeaponCell::WeaponCell(int row, int col) :Cell(row, col)
{
}


WeaponCell::~WeaponCell()
{
}

bool WeaponCell::ActOn(Player* p)
{
	return true;
}

bool WeaponCell::walkthrough(){
	return false;
}

string WeaponCell::Message(){
	return "Got Weapon!";
}
