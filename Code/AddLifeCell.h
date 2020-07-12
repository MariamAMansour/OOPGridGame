#pragma once
#include "Cell.h"

class AddLifeCell : public Cell{
public:
	AddLifeCell(int r, int c);
	virtual ~AddLifeCell();
	virtual bool ActOn(Player* p);
	virtual bool walkthrough();
	virtual string Message();
};