#pragma once
#include "ObstacleCell.h"

class StartPointCell :public ObstacleCell{
public:
	StartPointCell(int r, int c);
	virtual ~StartPointCell();
};