#pragma once
#include "Cell.h"

class CoinCell :public Cell{
public:
	CoinCell(int r, int c);
	virtual ~CoinCell();
	virtual bool ActOn(Player* p);
	virtual bool walkthrough();
	virtual string Message();
};