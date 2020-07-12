#pragma once
#include "Cell.h"

class PlayerCell :	public Cell
{
	
public:
	PlayerCell(int row, int col);
	virtual ~PlayerCell();
	virtual bool ActOn(Player* p);
	virtual bool walkthrough();
};
