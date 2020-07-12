#pragma once

#include "GUI.h"
#include "DEFS.h"
#include "Cell.h"
#include <vector>
class Player;	//forward class declaration
class Enemies;

class Grid
{
	GUI * pGUI;   // a pointer to the the interface
	Cell*	GameCells[NumRowCells][NumColumnCells];	// Array of Pointers to Cell
	Player* player;
	vector <Enemies*> allEnemies;	//a vector of pointers to all the moving cells of the enemies
	int Coins;		//Holds total number of coins in grid

public:

	Grid();	  

	// ========== Action-Related Functions ==========
	void GetCellClicked(int& r, int& c, bool wait);		//changes from GetPointClicked information from GUI to a specific r and c grid cell

	ActionType GetUserAction() const; // Reads the input command from the user and returns the corresponding action type

	void ExecuteAction(ActionType) ;  // Creates an action of the passed actionType and executes it
	void ExecuteLoadedAction(int r , int c, ActionType);

	void setCell(int r, int c, Cell* pCell);	//updates cell r,c to hold the new pointer pCell
	
	void MoveIfPossible(Cell * pCurrentCell, ActionType dir); // Moves the entered position in the passed direction if no obstacles
	                                                       // updates currentCell if move takes place
	                                                       // Note: It returns bool indicating if a move occured or not
	
	void MoveCells(Cell * CurrentCell);		//moves all cells that should move during gameplay. Namely, enemies.

	bool IsValidCell(int r, int c) const;

	void DrawAllCells() const; // Draws the Grid and All its GameObjects

	GUI * getGUI() const;	// Gets a Pointer to the GUI

	void Saveall() ;
	void Loadall() ;
	void Bombaction();			//Deploys bomb

	bool checkCoin(Cell*);		//Checks if given cell is a coin
	int inallEnemies(Cell*);	//Checks if given cell is in the allEnemies vector

	void PrintCellMessage(Cell*);
	void GameOver();
	void GameWon();

	~Grid();
	void RunApp();	//Runs the application

	void GameModeActions();
};

