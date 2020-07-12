#pragma once
#include "Cell.h"

class GameOverCell : public Cell{
public:
	GameOverCell(int r, int c);
	virtual ~GameOverCell();
	virtual bool ActOn(Player* p);
	virtual bool walkthrough();
	virtual string Message();
};