#pragma once
#include "cell.h"
class EmptyCell :
	public Cell
{
public:
	EmptyCell(int r, int c);
	virtual ~EmptyCell();
	virtual bool ActOn(Player* p);
	virtual bool walkthrough();
	virtual string Message();
};

