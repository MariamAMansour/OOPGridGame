#pragma once
#include "Cell.h"

class AddHealthCell :public Cell{
public:
	AddHealthCell(int r, int c);
	virtual ~AddHealthCell();
	virtual bool ActOn(Player* p);
	virtual bool walkthrough();
	virtual string Message();
};