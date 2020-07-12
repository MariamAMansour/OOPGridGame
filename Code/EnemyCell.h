#pragma once
#include "Cell.h"

class EnemyCell :public Cell{
public:
	EnemyCell(int r, int c);
	virtual ~EnemyCell();
	virtual bool ActOn(Player* p);
	virtual bool walkthrough();
	virtual string Message();
};