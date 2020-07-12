#include "Cell.h"
#include "Player.h"
#include "AddLifeCell.h"

using namespace std;

AddLifeCell::AddLifeCell(int r, int c) :Cell(r, c){
	ImagePath = "images\\Cells\\Full Life.jpg";
	Celltype = "AddLifeCell";
}

AddLifeCell::~AddLifeCell(){

}

bool AddLifeCell::ActOn(Player* p){
	p->addLife();
	return true;
}

bool AddLifeCell::walkthrough(){
	return false;
}

string AddLifeCell::Message(){
	return "Added Life!";
}