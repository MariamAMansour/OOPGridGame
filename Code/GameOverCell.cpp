#include "Cell.h"
#include "Player.h"
#include "GameOverCell.h"

using namespace std;

GameOverCell::GameOverCell(int r, int c) :Cell(r, c){
	ImagePath = "images\\Cells\\Game Over.jpg";
	Celltype = "GameOverCell";
}

GameOverCell::~GameOverCell(){

}


bool GameOverCell::ActOn(Player* p){
	p->GameOver();
	return false;
}

bool GameOverCell::walkthrough(){
	return false;
}

string GameOverCell::Message(){
	return "Garbage Truck!";
}