#pragma once

#include "Cell.h"
#include "GUI.h"
#include "Enemies.h"
class Grid;
enum Weapon{ bomb, slowdown, none};

class Player 
{	
	int lives;    // number of lives (initially 4)
	float health; // player's health percentage (initially 100% -> full health)
	float score;  // player's score (initially 0)
	Weapon weapon; //weapon player is carrying (initially None)
	Cell* PositionCell;
	bool Won;

public:
	
	Player(Cell* pos); // Constructor
	
	Cell* getPosition();
	void setPosition(Cell*);
	void Move(Grid* pGrid, ActionType MoveAction); // Moves the Player in a specific direction if possible and decreases the battery charge
	void addHealth();  //Adds 10 health when player collects a health icon
	void addLife();  //Adds life when player collects a life icon
	void addScore();  //Adds score when player collects a coin icon
	void touchEnemy();  //loses a life; resets health to 100
	void GameOver();  //sets lives to zero
	void setWon(bool);	//sets Won boolean
	void setWeapon(Weapon type); //sets weapon to input type if player is not already carrying a weapon
	Weapon getWeapon();
	int getLives();
	float getHealth();
	float getScore();
	bool getWon();		//getter functions
	bool alive();  //returns true if lives are not empty
	void setScore(float);
	void setHealth(float);
	
};

