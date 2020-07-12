#include "Cell.h"
#include "Player.h"
#include "CoinCell.h"

using namespace std;

CoinCell::CoinCell(int r, int c) : Cell(r, c){
	ImagePath = "images\\Cells\\Coin.jpg";
	Celltype = "CoinCell";
}

CoinCell::~CoinCell(){

}

bool CoinCell::ActOn(Player* p){
	p->addScore();
	return true;
}

bool CoinCell::walkthrough(){
	return false;
}

string CoinCell::Message(){
	return "Added Score!";
}