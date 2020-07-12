#include "GUI.h"
#include "Grid.h"
#include "Player.h"
#include "Enemies.h"
#include "AddHealthCell.h"
#include "AddLifeCell.h"
#include "CoinCell.h"
#include "EmptyCell.h"
#include "EnemyCell.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Enemy5.h"
#include "GameOverCell.h"
#include "GoalCell.h"
#include "ObstacleCell.h"
#include "Obstacle1.h"
#include "Obstacle2.h"
#include "WeaponCell.h"
#include "BombWeapon.h"
#include "SlowDownWeapon.h"
#include "StartPointCell.h"
#include "PlayerCell.h"
#include <string>
#include <fstream>
#include <sstream>
#include<iostream>


Grid::Grid() 
{
	// initializes all the GameObject pointer of the List to NULL
	for (int i = 0; i < NumRowCells; i++)
	{
		for (int j = 0; j < NumColumnCells; j++)		{
			
			GameCells[i][j] = new EmptyCell(i,j);	//start with all cells as empty cells
		}
	}
	pGUI = new GUI;
	DrawAllCells();
	allEnemies.reserve(10);
	Coins = 0;
	
}



/////////////////////////////////////////////////////////////////////////////////////////////
// Moves the entered position in the passed direction if possible
// updates currentCell if move takes place
// Note: It returns bool indicating if a move occured or not
void Grid::MoveIfPossible(Cell* pCurrentCell, ActionType dir)
{
	//Calculate the row and col of the cell to move to
	//First initialize them as current row and col
	int playerOldRow = pCurrentCell->getRow();
	int playerOldCol = pCurrentCell->getCol();

	int TargetRow = playerOldRow;
	int TargetCol = playerOldCol ; 

	
	switch(dir)
	{
	case MOVE_UP:
		TargetRow--;
		break;
	case MOVE_DOWN:
		TargetRow++;
		break;
	case MOVE_LEFT:
		TargetCol--;
		break;
	case MOVE_RIGHT:
		TargetCol++;;
		break;
	}

	if( !IsValidCell(TargetRow, TargetCol))
		return;

	//get the target cell
	Cell *pTargetCell = GameCells[TargetRow][TargetCol];

	if ((pTargetCell->getType()).compare("EmptyCell") !=0 )
	PrintCellMessage(pTargetCell);
	
	if (!pTargetCell->ActOn(player)){	//The target cell is an obstacle ==> no action should be taken
		int i = inallEnemies(pTargetCell);
		if ((i != -1) && (player->getWeapon() == slowdown)){
			allEnemies[i]->makeSlow();
			player->setWeapon(none);
		}
		return;
	}

	//The target cell is not an obstacle and has acted on the player
	//The player position should be updated to the target cell
	
	//Player should be moved to the target cell
	//1-delete the target cell and make it point to the PlayerCell
	setCell(TargetRow,TargetCol, pCurrentCell);

	//2- update player position
	pCurrentCell->SetRow(TargetRow);
	pCurrentCell->SetCol(TargetCol);

	//3- Convert the old player position to an Empty cell
	GameCells[playerOldRow][playerOldCol] = new EmptyCell(playerOldRow,playerOldCol);

	//4- Redraw both cells
	pGUI->DrawCell(GameCells[TargetRow][TargetCol]);
	pGUI->DrawCell(GameCells[playerOldRow][playerOldCol]);
}


void Grid::PrintCellMessage(Cell* c){
	string cell = c->Message();
	pGUI->PrintDynamicMessage(550, cell);

	
}

void Grid::DrawAllCells() const	
{
	// Draw Empty Grid
	pGUI->ClearGridArea();

	// Draw all the GameObject of the Grid
	for (int i = 0; i < NumRowCells; i++)
		for (int j = 0; j < NumColumnCells; j++)
			pGUI->DrawCell(GameCells[i][j]);
}

void Grid::setCell(int row, int col, Cell* pCell)
{	
	if (GameCells[row][col]){
			
		int i = inallEnemies(GameCells[row][col]);
			if (i != -1){		//Check on and delete enemy from the vector allEnemies
				delete[]allEnemies[i];
				allEnemies.erase(allEnemies.begin() + i);}		

		if (checkCoin(GameCells[row][col])) Coins--;	//Keep track of collected coins

		delete GameCells[row][col];	//if cell ptr is not null, delete it first
	}

	GameCells[row][col] = pCell;

}


bool Grid::checkCoin(Cell* c){
	if (c->getType() == "CoinCell"){
		return true;
	}
	return false;
}

int Grid::inallEnemies(Cell* c){
	for (int i = 0; i < allEnemies.size(); i++){
		if (c == allEnemies[i]->getPosition()) return i;
	}
		return -1;
}


GUI * Grid::getGUI() const
{
	return pGUI;
}
///////////////////////////////////////////////////////////////////
//				Action-related functions
///////////////////////////////////////////////////////////////////

ActionType Grid::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pGUI->GetUserAction( ); 
}

////////////////////////////////////////////////////////////////////////////////////
//Uses get point clicked to get the cell clicked in the grid
void Grid::GetCellClicked(int& r, int& c, bool wait){
	int x, y;
	int c1 = 0; 
	int c2 = 0;
		pGUI->GetPointClicked(x, y, true);
		for (int i = 0; i < 1100; i = i + 50){
			for (int j = 60; j<660; j = j + 50){
				if (x > i && x < i + 50 && y<j + 50 && y>j){
					r = c1;
					c = c2;
				}
				c1= c1+1;
			}
			c1 = 0;
			c2= c2+1;
		}

}

void Grid::Bombaction(){
	// This function is responsible for the bomb weapon action
	Cell* bombPos = player->getPosition();
	//looping on rows +-3
	for (int i =-3; i <= 3; i++){
		int flag1 = 0;
		int x = bombPos->getRow() + i;  //getting player position
		int y = bombPos->getCol() ;
		if (x > 0 && y > 0){
			Cell* C = GameCells[x][y];
			//Checking of the type of the cell 
			if (C->getType().compare("Enemy1") == 0 || C->getType().compare("Enemy2") == 0 || C->getType().compare("Enemy3") == 0 ||
				C->getType().compare("Enemy4") == 0 || C->getType().compare("Enemy5") == 0 ){
				if (i < 0){
					for (int k = i + 1; k < 0; k++){  //checking for obstacles
						Cell* C1 = GameCells[bombPos->getRow() - k][y];
						if (C1->getType().compare("Obstacle1") == 0 || C1->getType().compare("Obstacle2") == 0)
							flag1 = 1;
					}
				}
				if (i > 0){
					for (int k = i - 1; k > 0; k--){  //checking for obstacles
						Cell* C1 = GameCells[bombPos->getRow() - k][y];
						if (C1->getType().compare("Obstacle1") == 0 || C1->getType().compare("Obstacle2") == 0)
							flag1 = 1;
					}
				}
				if (flag1 == 0){
					EmptyCell* eCell = new EmptyCell(x, y);
					setCell(x, y, eCell);
					pGUI->DrawCell(eCell);
				}
				}
			}
		}
	//looping on columns +-3
	for (int j = -3; j <= 3; j++){
		int flag1 = 0;
		int x = bombPos->getRow();
		int y = bombPos->getCol()+ j;

		if (x > 0 && y > 0){
			Cell* C = GameCells[x][y];
			//Checking of the type of the cell 
			if (C->getType().compare("Enemy1") == 0 || C->getType().compare("Enemy2") == 0 || C->getType().compare("Enemy3") == 0 ||
				C->getType().compare("Enemy4") == 0 || C->getType().compare("Enemy5") == 0){
				if (j < 0){
					for (int k = j + 1; k < 0; k++){  //checking for obstacles
						Cell* C2 = GameCells[x][bombPos->getCol() + k];
						if (C2->getType().compare("Obstacle1") == 0 || C2->getType().compare("Obstacle2") == 0)
							flag1 = 1;
					}
				}
				if (j > 0){
					for (int k = j - 1; k > 0; k--){  //checking for obstacles
						Cell* C2 = GameCells[x][bombPos->getCol() + k];
						if (C2->getType().compare("Obstacle1") == 0 || C2->getType().compare("Obstacle2") == 0)
							flag1 = 1;
					}
				}
				if (flag1 == 0){
					EmptyCell* eCell = new EmptyCell(x, y);
					setCell(x, y, eCell);
					pGUI->DrawCell(eCell);
					player->setWeapon(none);
				}
			}
		}
	}
	
}
//Save function
void Grid:: Saveall() {
	string fsname;  //variable that we will get from the user
	ofstream savefile;  //creating outputfile object

	//getting the savefile name

	pGUI->PrintMessage(10,"Please enter file name:");

	fsname = pGUI->GetSrting();

	//adding the txt extension
	fsname = fsname.append(".txt");

	//opening the savefile
	savefile.open(fsname.c_str());
	savefile << to_string(player->getHealth()) << " " << to_string(player->getScore()) << " " << player->getWeapon()<<endl;
	//looping on the non-empty cells and saving them
	for (int i = 0; i < NumRowCells; i++){
		for (int j = 0; j < NumColumnCells; j++){
			if (GameCells[i][j]->getType() != "EmptyCell")
				savefile << GameCells[i][j]->getType() << " " << i << " " << j << endl;  // get-type is used instead of the save function
																							// I found it better that way
		}
	}
	

	savefile.close();
}

//load function
void Grid::Loadall(){

	string fname;
	ifstream loadfile;
	string a;
	string type;
	int loadrow;
	int loadcol;
	int i = 1;
	//int pr;
	//int pc;


	pGUI->PrintMessage(10,"Please enter file name:");
	fname = pGUI->GetSrting();
	fname = fname.append(".txt");
	loadfile.open(fname.c_str());

	//clearing any added modifictions by the user
	for (int i = 0; i < NumRowCells; i++){
		for (int j = 0; j < NumColumnCells; j++){
			EmptyCell* nCell = new EmptyCell(i, j);
			setCell(i, j, nCell);
			pGUI->DrawCell(nCell);
		}
	}

	///extracting the player data first
	float h;
	float sc;
	int w;
	loadfile >> h >> sc >> w;
	player->setHealth(h);
	player->setScore(sc);
	if (w == 0)
		player->setWeapon(bomb);
	else if (w == 1)
		player->setWeapon(slowdown);
	else
		player->setWeapon(none);


	//looping on the lines of the loading cells data
	while (loadfile >> type >> loadrow >> loadcol){

	//Creating the objects while reading from the loading file
	if (type.compare("Enemy1") == 0){
		Enemy1* nCell = new Enemy1(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction( loadrow, loadcol,ENEMY1);
		
	}


	else if (type.compare("Enemy2") == 0){
		Enemy2* nCell = new Enemy2(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction(loadrow, loadcol, ENEMY2);
	}


	else if (type.compare("Enemy3") == 0){
		Enemy3* nCell = new Enemy3(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction(loadrow, loadcol, ENEMY3);
	}

	else if (type.compare("Enemy4") == 0){
		Enemy4* nCell = new Enemy4(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction(loadrow, loadcol, ENEMY4);
	}
	else if (type.compare("Enemy5") == 0){
		Enemy5* nCell = new Enemy5(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction(loadrow, loadcol, ENEMY5);
	}
	else if (type.compare("Obstacle1") == 0){
		Obstacle1* nCell = new Obstacle1(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction(loadrow, loadcol, OBSTACLE1);
	}
	else if (type.compare("Obstacle2") == 0){
		Obstacle2* nCell = new Obstacle2(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction(loadrow, loadcol, OBSTACLE2);
	}

	else if (type.compare("StartPointCell") == 0){
		StartPointCell* nCell = new StartPointCell(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction(loadrow, loadcol, STARTPOINT);
	}


	else if (type.compare("CoinCell") == 0){
		CoinCell* nCell = new CoinCell(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction(loadrow, loadcol, COIN);
	}

	else if (type.compare("AddHealthCell") == 0){
		AddHealthCell* nCell = new AddHealthCell(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction(loadrow, loadcol, HEALTH);
	}

	else if (type.compare("AddLifeCell") == 0){
		AddLifeCell* nCell = new AddLifeCell(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction(loadrow, loadcol, LIFE);
	}

	else if (type.compare("Empty") == 0){
		EmptyCell* nCell = new EmptyCell(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction(loadrow, loadcol, EMPTY);
	}

	else if (type.compare("GameOverCell") == 0){
		GameOverCell* nCell = new GameOverCell(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction(loadrow, loadcol, GAMEOVER);
	}

	else if (type.compare("GoalCell") == 0){
		GoalCell* nCell = new GoalCell(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction(loadrow, loadcol, GOAL);
	}

	else if (type.compare("PlayerCell") == 0){
		PlayerCell* nCell = new PlayerCell(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction(loadrow, loadcol, PLAYER);

		
	}
	else if (type.compare("BombWeapon") == 0){
		BombWeapon* nCell = new BombWeapon(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction(loadrow, loadcol, BOMB);

	}

	else if (type.compare("SlowDownWeapon") == 0){
		SlowDownWeapon* nCell = new SlowDownWeapon(loadrow, loadcol);
		setCell(loadrow, loadcol, nCell);
		pGUI->DrawCell(nCell);
		ExecuteLoadedAction(loadrow, loadcol, SLOWDOWN);

	}
	
	//closing the while loop
	}



loadfile.close();
}

void Grid::MoveCells(Cell* CurrentCell){
	while (1){
		int OldRow = CurrentCell->getRow();
		int OldCol = CurrentCell->getCol();

		int TargetRow = OldRow;
		int TargetCol = OldCol;
		int move = rand() % 4;

		switch (move)
		{
		case 0:
			TargetRow--;
			break;
		case 1:
			TargetRow++;
			break;
		case 2:
			TargetCol--;
			break;
		case 3:
			TargetCol++;
			break;
		}

		if (!IsValidCell(TargetRow, TargetCol))
			continue;

		//get the target cell
		Cell *TargetCell = GameCells[TargetRow][TargetCol];

		if (!TargetCell->walkthrough()){
			if (TargetCell == player->getPosition()){
				int i = inallEnemies(CurrentCell);
				if (player->getWeapon() == slowdown){
					allEnemies[i]->makeSlow();
					player->setWeapon(none);
				}
				CurrentCell->ActOn(player);
			}
			continue;
		}


		setCell(TargetRow, TargetCol, CurrentCell);
		//2- update cell position
		CurrentCell->SetRow(TargetRow);
		CurrentCell->SetCol(TargetCol);
		
		//3- Convert the old cell position to an Empty cell
		GameCells[OldRow][OldCol] = new EmptyCell(OldRow, OldCol);

		//4- Redraw both cells
		pGUI->DrawCell(GameCells[TargetRow][TargetCol]);
		pGUI->DrawCell(GameCells[OldRow][OldCol]);
		break;
	}
}
// Excutes actions of loaded files
void Grid::ExecuteLoadedAction(int r,int c,ActionType ActType)
{


	// According to Action Type, create the corresponding action object	
	switch (ActType)
	{
	case LOAD:
		// Call Load function to load game from a file
		Grid::Loadall();
		break;

	case SAVE:
		// Calling the save all function
		Grid::Saveall();
		break;

	case START:{	//start game 
		pGUI->setInterfaceMode(MODE_GAME);
		if (player->getWeapon() == bomb)
				pGUI->Converttogame(player->getLives(), 1);
			 else if (player->getWeapon() == slowdown)
					   pGUI->Converttogame(player->getLives(), 2);
			  else
					   pGUI->Converttogame(player->getLives(), 0);


	}

		break;

	case PAUSE:{	//pause game
		 pGUI->setInterfaceMode(MODE_MENU);
		  pGUI->Converttomenu(); }
		break;

		///TODO: Add a case for EACH Action type
	case MOVE_UP:
	case MOVE_DOWN:
	case MOVE_RIGHT:
	case MOVE_LEFT:
		player->Move(this, ActType);
		break;
	case EMPTYCELL:{
					   
			pGUI->PrintDynamicMessage(10, "Choose where to insert emptycell:");
			pGUI->ClearStatusBar();
			EmptyCell* nCell = new EmptyCell(r, c);
			setCell(r, c, nCell);
			pGUI->DrawCell(nCell); }
		break;
	case PLAYER:{	
			pGUI->ClearStatusBar();
			PlayerCell* nCell = new PlayerCell(r, c);
			setCell(r, c, nCell);
			pGUI->DrawCell(nCell);
			Cell* oldPos = player->getPosition();
			EmptyCell* eCell = new EmptyCell(oldPos->getRow(), oldPos->getCol());
			setCell(oldPos->getRow(), oldPos->getCol(), eCell);
			pGUI->DrawCell(eCell);
			player->setPosition(nCell); }
		break;
	case STARTPOINT:{
			pGUI->ClearStatusBar();
			StartPointCell* nCell = new StartPointCell(r, c);
			setCell(r, c, nCell);
			pGUI->DrawCell(nCell); }
		break;
	case GOAL:{
					 
		 pGUI->ClearStatusBar();
		 GoalCell* nCell = new GoalCell(r, c);
		 setCell(r, c, nCell);
		 pGUI->DrawCell(nCell); }
		break;
	case HEALTH:{
						
			pGUI->ClearStatusBar();
			AddHealthCell* nCell = new AddHealthCell(r, c);
			setCell(r, c, nCell);
			pGUI->DrawCell(nCell); }
		break;
	case COIN:{
			Coins++;
			pGUI->ClearStatusBar();
			CoinCell* nCell = new CoinCell(r, c);
			setCell(r, c, nCell);
			pGUI->DrawCell(nCell); }
		break;
	case OBSTACLE1:{		
			  pGUI->ClearStatusBar();
			  Obstacle1* nCell = new Obstacle1(r, c);
			  setCell(r, c, nCell);
			  pGUI->DrawCell(nCell); }
		break;
	case OBSTACLE2:{
			 pGUI->ClearStatusBar();
			  Obstacle2* nCell = new Obstacle2(r, c);
			  setCell(r, c, nCell);
			  pGUI->DrawCell(nCell); }
		break;
	case ENEMY1:{
				
			pGUI->ClearStatusBar();
			Enemy1* nCell = new Enemy1(r, c);
			setCell(r, c, nCell);
			pGUI->DrawCell(nCell);
			Enemies* enemy = new Enemies(nCell);
			allEnemies.push_back(enemy); }
		break;
	case ENEMY2:{
				
		pGUI->ClearStatusBar();
		Enemy2* nCell = new Enemy2(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell);
		Enemies* enemy = new Enemies(nCell);
		allEnemies.push_back(enemy); }
		break;
	case ENEMY3:{
				
		pGUI->ClearStatusBar();
		Enemy3* nCell = new Enemy3(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell);
		Enemies* enemy = new Enemies(nCell);
		allEnemies.push_back(enemy); }
		break;
	case ENEMY4:{
			pGUI->ClearStatusBar();
			Enemy4* nCell = new Enemy4(r, c);
			setCell(r, c, nCell);
			pGUI->DrawCell(nCell);
			Enemies* enemy = new Enemies(nCell);
			allEnemies.push_back(enemy); }
		break;
	case ENEMY5:{
					

			pGUI->ClearStatusBar();
			Enemy5* nCell = new Enemy5(r, c);
			setCell(r, c, nCell);
			pGUI->DrawCell(nCell);
			Enemies* enemy = new Enemies(nCell);
			allEnemies.push_back(enemy); }
		break;
	case LIFE:{
				  

			pGUI->ClearStatusBar();
			AddLifeCell* nCell = new AddLifeCell(r, c);
			setCell(r, c, nCell);
			pGUI->DrawCell(nCell); }
		break;
	case GAMEOVER:{

			pGUI->ClearStatusBar();
			GameOverCell* nCell = new GameOverCell(r, c);
			setCell(r, c, nCell);
			pGUI->DrawCell(nCell);
			Enemies* enemy = new Enemies(nCell);
			allEnemies.push_back(enemy); }
		break;
	case BOMB:{
				  

		 pGUI->ClearStatusBar();
		BombWeapon* nCell = new BombWeapon(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell);

	}
		break;
	case SLOWDOWN:{
					 

			 pGUI->ClearStatusBar();
			SlowDownWeapon* nCell = new SlowDownWeapon(r, c);
			setCell(r, c, nCell);
			pGUI->DrawCell(nCell); }
		break;
	case Bombenemies:
		if (player->getWeapon() == bomb){
			Grid::Bombaction();
		}
		break;
	case STATUS:	// a click on the status bar ==> no action
		return;
	}
}





// Creates an action and executes it
void Grid::ExecuteAction(ActionType ActType)
{


	// According to Action Type, create the corresponding action object	
	switch (ActType)
	{
	case LOAD:
		// Call Load function to load game from a file
		Grid::Loadall();
		break;

	case SAVE:
		// Calling the save all function
		Grid::Saveall();
		break;

	case START:{	//start game 
		 pGUI->setInterfaceMode(MODE_GAME);
				if (player->getWeapon() == bomb)
					   pGUI->Converttogame(player->getLives(), 1);
				else if (player->getWeapon() == slowdown)
					   pGUI->Converttogame(player->getLives(), 2);
				else
					   pGUI->Converttogame(player->getLives(), 0); 

	
	}

		break;

	case PAUSE:{	//pause game
		pGUI->setInterfaceMode(MODE_MENU);
		pGUI->Converttomenu(); }
		break;

	///TODO: Add a case for EACH Action type
	case MOVE_UP:
	case MOVE_DOWN:
	case MOVE_RIGHT:
	case MOVE_LEFT:
		player->Move(this, ActType);
		break;
	case EMPTYCELL:{
		int r, c;
		pGUI->PrintDynamicMessage(10, "Choose where to insert emptycell:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		EmptyCell* nCell = new EmptyCell(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell); }
		break;
	case PLAYER:{
		int r, c;
		pGUI->PrintDynamicMessage(10, "Choose where to insert Player:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		PlayerCell* nCell = new PlayerCell(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell);
		Cell* oldPos = player->getPosition();
		EmptyCell* eCell = new EmptyCell(oldPos->getRow(), oldPos->getCol());
		setCell(oldPos->getRow(), oldPos->getCol(), eCell);
		pGUI->DrawCell(eCell);
		player->setPosition(nCell); }
		break;
	case STARTPOINT:{
		int r, c;
		pGUI->PrintDynamicMessage(10, "Choose where to insert StartPoint:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		StartPointCell* nCell = new StartPointCell(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell); }
		break;
	case GOAL:{
		int r, c;
		pGUI->PrintDynamicMessage(10, "Choose where to insert Goal:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		GoalCell* nCell = new GoalCell(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell); }
		break;
	case HEALTH:{
		int r, c;
		pGUI->PrintDynamicMessage(10, "Choose where to insert Health:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		AddHealthCell* nCell = new AddHealthCell(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell); }
		break;
	case COIN:{
		Coins++;
		int r, c;
		pGUI->PrintDynamicMessage(10, "Choose where to insert Coin:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		CoinCell* nCell = new CoinCell(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell); }
		break;
	case OBSTACLE1:{
		int r, c;
		pGUI->PrintDynamicMessage(10, "Choose where to insert Obstacle1:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		Obstacle1* nCell = new Obstacle1(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell); }
		break;
	case OBSTACLE2:{
		int r, c;
		pGUI->PrintDynamicMessage(10, "Choose where to insert Obstacle2:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		Obstacle2* nCell = new Obstacle2(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell); }
		break;
	case ENEMY1:{
		int r, c;
		pGUI->PrintDynamicMessage(10, "Choose where to insert Enemy1:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		Enemy1* nCell = new Enemy1(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell);
		Enemies* enemy = new Enemies(nCell);
		allEnemies.push_back(enemy); } 
		break;
	case ENEMY2:{
		int r, c;	
		pGUI->PrintDynamicMessage(10, "Choose where to insert Enemy2:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		Enemy2* nCell = new Enemy2(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell);
		Enemies* enemy = new Enemies(nCell);
		allEnemies.push_back(enemy); }
		break;
	case ENEMY3:{
		int r, c;
		pGUI->PrintDynamicMessage(10, "Choose where to insert Enemy3:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		Enemy3* nCell = new Enemy3(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell);
		Enemies* enemy = new Enemies(nCell);
		allEnemies.push_back(enemy); }
		break;
	case ENEMY4:{
		int r, c;
		pGUI->PrintDynamicMessage(10, "Choose where to insert Enemy4:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		Enemy4* nCell = new Enemy4(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell);
		Enemies* enemy = new Enemies(nCell);
		allEnemies.push_back(enemy); }
		break;
	case ENEMY5:{
		int r, c;
		pGUI->PrintDynamicMessage(10, "Choose where to insert Enemy5:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		Enemy5* nCell = new Enemy5(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell);
		Enemies* enemy = new Enemies(nCell);
		allEnemies.push_back(enemy); }
		break;
	case LIFE:{
		int r, c;
		pGUI->PrintDynamicMessage(10, "Choose where to insert Life:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		AddLifeCell* nCell = new AddLifeCell(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell); }
		break;
	case GAMEOVER:{
		int r, c;
		pGUI->PrintDynamicMessage(10, "Choose where to insert Gameover Cell:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		GameOverCell* nCell = new GameOverCell(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell);
		Enemies* enemy = new Enemies(nCell);
		allEnemies.push_back(enemy); }
		break;
	case BOMB:{
		int r, c;
		pGUI->PrintDynamicMessage(10, "Choose where to insert Bomb Weapon:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		BombWeapon* nCell = new BombWeapon(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell);

	}
		break;
	case SLOWDOWN:{
		int r, c;
		pGUI->PrintDynamicMessage(10, "Choose where to insert Slowdown Weapon:");
		GetCellClicked(r, c, true);
		pGUI->ClearStatusBar();
		SlowDownWeapon* nCell = new SlowDownWeapon(r, c);
		setCell(r, c, nCell);
		pGUI->DrawCell(nCell); }
		break;
	case Bombenemies:
		if (player->getWeapon() == bomb){
			Grid::Bombaction();
		}
		break;
	case STATUS:	// a click on the status bar ==> no action
		return;
	}
}

Grid::~Grid()
{
	delete pGUI;
}

//////////////////////////////////////////////////////////////////////////////////


// Runs the application

void Grid::RunApp()
{
	
	int row = 0, col = 0;	
	PlayerCell* pCell = new PlayerCell(row,col);
	setCell(row,col, pCell);
	player = new Player(pCell);
	pGUI->DrawCell(pCell);
	for (int i = 0;; i++) {
		GUI_MODE mode = pGUI->getInterfaceMode();

		if (mode == MODE_GAME){				
			GameModeActions();
			if (i % 5 == 0){			//Moving Enemies
			for (int j = 0; j < allEnemies.size(); j++){
				if (!allEnemies[j]->isSlowed()){
					allEnemies[j]->Move(this);}
				else if (i % 10 == 0){
					allEnemies[j]->Move(this);
				}}}
		}

		ActionType act = GetUserAction();
		if (act == EXIT){
			pGUI->PrintMessage(10, "press y to save and n to exit");
			string choice;
			choice=pGUI->GetSrting();
			if (choice.compare("y") == 0 || choice.compare("Y") == 0)
				Grid::Saveall();
			else
			return;
		}

		ExecuteAction(act);

		Sleep(100);
	}
}

void Grid::GameModeActions(){
	pGUI->PrintDynamicMessage(10, "Player Health:");
	pGUI->PrintDynamicMessage(280, "Player score:");
	pGUI->PrintDynamicMessage(130, to_string(player->getHealth()));
	pGUI->PrintDynamicMessage(390, to_string(player->getScore()));


	static int l = player->getLives();
	static Weapon w = player->getWeapon();
	if ((l != player->getLives()) || (w != player->getWeapon())){
		if (player->getWeapon() == bomb)
			pGUI->Converttogame(player->getLives(), 1);
		else if (player->getWeapon() == slowdown)
			pGUI->Converttogame(player->getLives(), 2);
		else
			pGUI->Converttogame(player->getLives(), 0);
		l = player->getLives();
		w = player->getWeapon();
	}
	
	if (!player->alive()){
		GameOver();
	}

	if (player->getWon()){
		GameWon();
	}
}

void Grid::GameOver(){
		pGUI->setInterfaceMode(MODE_MENU);
		pGUI->Converttomenu();
		pGUI->PrintDynamicMessage(10, "Game Over!");
		pGUI->PrintDynamicMessage(130, "      ");
}

void Grid::GameWon(){
	if (Coins == 0){
		pGUI->setInterfaceMode(MODE_MENU);
		pGUI->Converttomenu();
		pGUI->PrintDynamicMessage(10, "Game Won!");
		pGUI->PrintDynamicMessage(130, "      ");
	}
	else{
		pGUI->PrintDynamicMessage(500, "Collect Money!");
		Sleep(500);
		pGUI->PrintDynamicMessage(500, "                 ");
		player->setWon(false);
	}
}

////////////////////////////////////////////////////////////////////////////////////
bool Grid::IsValidCell(int row, int col) const
{
	return (row >= 0 && row < NumRowCells) 
			&& (col >=0 && col < NumColumnCells);
}
