#include "ObstacleCell.h"
#include "Obstacle1.h"

using namespace std;

Obstacle1::Obstacle1(int r, int c) :ObstacleCell(r, c){
	ImagePath = "images\\Cells\\Obstacle1.jpg";
	Celltype = "Obstacle1";
}


Obstacle1::~Obstacle1(){

}