#include "EnemyCell.h"
#include "Enemy2.h"

using namespace std;

Enemy2::Enemy2(int r, int c) :EnemyCell(r, c){
	ImagePath = "images\\Cells\\shoe2.jpg";
	Celltype = "Enemy2";
}

Enemy2::~Enemy2(){

}