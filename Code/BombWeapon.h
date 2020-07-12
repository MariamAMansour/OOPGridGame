#pragma once
#include "WeaponCell.h"

class BombWeapon : public WeaponCell
{

public:
	BombWeapon(int row, int col);
	virtual ~BombWeapon();
	virtual bool ActOn(Player* p);
};