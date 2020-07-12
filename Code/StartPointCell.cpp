#include "ObstacleCell.h"
#include "StartPointCell.h"

using namespace std;

StartPointCell::StartPointCell(int r, int c) :ObstacleCell(r, c){
	ImagePath = "images\\Cells\\Start Cell.jpg";
	Celltype = "StartPointCell";
}

StartPointCell::~StartPointCell(){

}