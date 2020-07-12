#include "Cell.h"
#include "Player.h"
#include "AddHealthCell.h"

using namespace std;

AddHealthCell::AddHealthCell(int r, int c) :Cell(r, c){
	ImagePath = "images\\Cells\\Add Health.jpg";
	Celltype = "AddHealthCell";
}

AddHealthCell::~AddHealthCell(){

}

bool AddHealthCell::ActOn(Player* p){
	p->addHealth();
	return true;
}

bool AddHealthCell::walkthrough(){
	return false;
}

string AddHealthCell::Message(){
	return "Added Health!";
}