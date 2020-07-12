#include "Player.h"
#include "Enemies.h"
#include "Grid.h"
#include "GUI.h"

Player::Player(Cell* pos)
{
	PositionCell = pos;
	lives = 4;
	health = 100;
	score = 0;
	weapon = none;
	Won = false;
	// Makes all the needed initialization
}

void Player::Move(Grid* pGrid, ActionType dir)
{
	//Player's battery decreases every step:
	health = health - 2;
	if (health == 0){
		lives--;
		if (alive())
			health = 100;
	}

	// Check if the Move is Possible (No Obstacles)
	pGrid->MoveIfPossible(PositionCell, dir); // if the move is possible, position will be changed (passed by ref)
	
}

void Player::setPosition(Cell* pos)
{
	PositionCell = pos;
}

Cell* Player::getPosition(){
	return PositionCell;
}

bool Player::alive(){
	if (lives == 0){
		return false;
	}
		return true;
}

void Player::touchEnemy(){
	if (weapon != slowdown){
		lives--;
		health = 100;
	}

}

void Player::GameOver(){
	lives = 0;
	health = 0;
}

void Player::addHealth(){
	if (health != 100)
		health = health + 10;
}

void Player::addLife(){
	if (lives != 4)
		lives++;
}

void Player::addScore(){
	score++;
}

void Player::setWeapon(Weapon type){
	if (weapon == none || type == none){
		weapon = type;
	}
}

void Player::setWon(bool w){
	Won = w;
}


Weapon Player::getWeapon(){
	return weapon;
}
int Player::getLives(){
	return lives;
}
float Player::getHealth(){
	return health;
}
float Player::getScore(){
	return score;
}
void Player::setScore(float s){
	score = s;
}
void Player::setHealth(float h){
	health = h;
}
bool Player::getWon(){
	return Won;
}

