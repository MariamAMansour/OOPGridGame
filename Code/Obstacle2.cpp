#include "ObstacleCell.h"
#include "Obstacle2.h"

using namespace std;

Obstacle2::Obstacle2(int r, int c) :ObstacleCell(r, c){
	ImagePath = "images\\Cells\\Obstacle2.jpg";
	Celltype = "Obstacle2";
}


Obstacle2::~Obstacle2(){

}