#include "Cell.h"
#include "Player.h"
#include "EnemyCell.h"


using namespace std;

EnemyCell::EnemyCell(int r, int c) : Cell(r, c){
}

EnemyCell::~EnemyCell(){

}

bool EnemyCell::ActOn(Player* p){
	p->touchEnemy();
	return false;
}

bool EnemyCell::walkthrough(){
	return false;
}

string EnemyCell::Message(){
	return "Enemy Hit!";
}