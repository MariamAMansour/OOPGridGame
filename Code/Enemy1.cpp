#include "EnemyCell.h"
#include "Enemy1.h"

using namespace std;

Enemy1::Enemy1(int r, int c) :EnemyCell(r, c){
	ImagePath = "images\\Cells\\shoe1.jpg";
	Celltype = "Enemy1";
}


Enemy1::~Enemy1(){

}