#pragma once
#include "Cell.h"

class ObstacleCell : public Cell{
public:
	ObstacleCell(int r, int c);
	virtual ~ObstacleCell();

	virtual bool ActOn(Player* p);
	virtual bool walkthrough();
	virtual string Message();
};