#pragma once 
#include <string>
using namespace std;

	// note: this class does NOT deal with real coordinates, it deals with the cell number instead
	// Example: if row = 1 and col = 2 --> that means cell with ** in the grid drawn below

	// any pair is: (row, col)

	// ----------------------------
	// | (0,0) | (0,1) | (0,2)   |
	// ----------------------------
	// | (1,0) | (1,1) | (1,2)** |
	// ----------------------------
	// | (2,0) | (2,1) | (2,2)   |
	// ----------------------------



class Player;
class Cell
{
	int row;	//the row of the cell (from 0 to number of rows-1)
	int col;	//the col of the cell (from 0 to number of columns -1)
protected:
	string ImagePath;	//each cell has associated image
	string Celltype;

public:

	Cell (); // Initializes the cell to (-1,-1) indicating uninitialized with valid values
	Cell (int , int ); // Sets row and col if valid

	bool SetRow(int ); // The setter of row (the setter here sets only if the the cell is in grid range)
	bool SetCol(int ); // The setter of col (the setter here sets only if the the cell is in grid range)

	int getRow() const; // The getter of row
	int getCol() const; // The getter of col


	virtual bool ActOn(Player* p) ;	//Takes appropriate action on the player according to cell type
	//This function should be overriden by each derived cell class

	virtual bool walkthrough(); //returns whether moving cells (other than player) can walk thorugh this cell

	string getImage() const;	//return image of the cell
	string getType() const;  //returns type of the cell this is used instead of the save function, I found it will be easier this way and 
	// more computationally optimized
	bool operator == (const Cell & other) const; // Operator Overloading : Check if the passed cell equals the current cell
	bool operator != (const Cell & other) const; // Operator Overloading : Check if the passed cell does NOT equal the current cell

	virtual string Message();

	virtual ~Cell();

};

