#include "BombWeapon.h"
#include "Player.h"
#include "WeaponCell.h"
#include "Grid.h"

BombWeapon::BombWeapon(int row, int col) :WeaponCell(row, col)
{
	ImagePath = "images\\Cells\\BombWeapon.jpg";
	Celltype = "BombWeapon";
}


BombWeapon::~BombWeapon()
{
}



bool BombWeapon::ActOn(Player* p)
{
	p->setWeapon(bomb);
	return true;
}