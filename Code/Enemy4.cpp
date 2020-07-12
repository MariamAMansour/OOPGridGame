#include "EnemyCell.h"
#include "Enemy4.h"

using namespace std;

Enemy4::Enemy4(int r, int c) :EnemyCell(r, c){
	ImagePath = "images\\Cells\\shoe4.jpg";
	Celltype = "Enemy4";
}


Enemy4::~Enemy4(){

}