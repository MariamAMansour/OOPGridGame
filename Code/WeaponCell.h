#pragma once
#include "Cell.h"

class WeaponCell : public Cell
{

public:
	WeaponCell(int row, int col);
	virtual ~WeaponCell();
	virtual bool ActOn(Player* p);
	virtual bool walkthrough();
	virtual string Message();
};