#include "Cell.h"
#include "Player.h"
#include "ObstacleCell.h"

using namespace std;

ObstacleCell::ObstacleCell(int r, int c) :Cell(r, c){

	Celltype = "ObstacleCell";
}

ObstacleCell::~ObstacleCell(){

}

bool ObstacleCell::ActOn(Player* p){
	return false;
}

bool ObstacleCell::walkthrough(){
	return false;
}

string ObstacleCell::Message(){
	return "Obstacle!";
}