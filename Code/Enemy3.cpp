#include "EnemyCell.h"
#include "Enemy3.h"

using namespace std;

Enemy3::Enemy3(int r, int c) :EnemyCell(r, c){
	ImagePath = "images\\Cells\\shoe3.jpg";
	Celltype = "Enemy3";
}

Enemy3::~Enemy3(){

}