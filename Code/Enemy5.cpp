#include "EnemyCell.h"
#include "Enemy5.h"

using namespace std;

Enemy5::Enemy5(int r, int c) :EnemyCell(r, c){
	ImagePath = "images\\Cells\\shoe5.jpg";
	Celltype = "Enemy5";
}

Enemy5::~Enemy5(){

}