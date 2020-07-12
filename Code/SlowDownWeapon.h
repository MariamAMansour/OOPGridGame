#pragma once
#include "WeaponCell.h"

class SlowDownWeapon : public WeaponCell
{

public:
	SlowDownWeapon(int row, int col);
	virtual ~SlowDownWeapon();
	virtual bool ActOn(Player* p);
};