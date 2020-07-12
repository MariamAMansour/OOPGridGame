#include "SlowDownWeapon.h"
#include "Player.h"
#include "WeaponCell.h"


SlowDownWeapon::SlowDownWeapon(int row, int col) :WeaponCell(row, col)
{
	ImagePath = "images\\Cells\\SlowDownWeapon.jpg";
	Celltype = "SlowDownWeapon";
}


SlowDownWeapon::~SlowDownWeapon()
{
}

bool SlowDownWeapon::ActOn(Player* p)
{
	p->setWeapon(slowdown);
	return true;
}