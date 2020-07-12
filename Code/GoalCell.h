#pragma once
#include "Cell.h"

class GoalCell : public Cell{
public:
	GoalCell(int r, int c);
	virtual ~GoalCell();
	virtual bool ActOn(Player* p);
	virtual bool walkthrough();
	virtual string Message();
};