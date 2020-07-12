#include "GUI.h"
#include "Player.h"

GUI::GUI()
{

	// Colors

	MsgColor = DARKRED;		    // StatusBar Messages color
	BkGrndColor = DARKSLATEBLUE;	// Grid Background color
	StatusBarColor = GREY;       // StatusBar Background color

	GridLineColor = LIGHTGRAY;   // Vertical and Horizontal Lines
	ObstacleColor = BLACK;       // Background of Obstacles
	
	// Create the output window
	pWind = new window(WindWidth + 15, WindHeight, 5, 5); 

	// Change the title
	pWind->ChangeTitle("Game");
		
	CreateMenu();
	ClearGridArea();
	ClearStatusBar();
	ClearDynamicStatusBar(150);

	InterfaceMode = MODE_MENU;
}


//window* GUI::CreateWind(int w, int h, int x, int y) const
//{ 
//	window* pW = new window(w, h, x, y);
//	/*pW->SetBrush(BkGrndColor);
//	pW->SetPen(BkGrndColor, 1);
//	pW->DrawRectangle(0, ToolBarHeight, w, h);	*/
//	return pW;
//}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::GetPointClicked(int &x, int &y, bool wait) const
{
	if(wait)
		pWind->WaitMouseClick(x, y); // wait (pause) till a mouse click
	else
		pWind->GetMouseClick(x, y);	 // no wait
}

////////////////////////////////////////////////////////////////////////////////////////// 

string GUI::GetSrting() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	// ESCAPE key is pressed
			return "";	// returns nothing as user has cancelled label
		if(Key == 13 )	// ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	// BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		
		PrintMessage(10, Label);
	}
}

//======================================================================================//
//								Game  Functions									        //
//======================================================================================//

ActionType GUI::GetUserAction() const
{	
	int x = -1, y = -1;
	

	//  ============ GUI in the MODE_MENU mode ============
	if ( InterfaceMode == MODE_MENU )	
	{
		pWind->WaitMouseClick(x, y);
		// [1] If user clicks on the Toolbar
		if ( y >= 0 && y < ToolBarHeight)
		{	
			// Check which Menu item was clicked
			// ==> This assumes that menu items are lined up horizontally <==

			int ClickedItemOrder = (x / MenuItemWidth);

			// Divide x coord of the point clicked by the menu item width (integer division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_LOAD: return LOAD;
			case ITM_SAVE: return SAVE;
			case ITM_START:
				pWind->FlushKeyQueue();
				pWind->FlushMouseQueue();
				return START;
			case ITM_EXIT: return EXIT;

			///TODO: Add cases for the other items of Create-Grid Mode
			case ITM_EMPTY: return EMPTYCELL;
			case ITM_PLAYER: return PLAYER;
			case ITM_STARTPOINT: return STARTPOINT;
			case ITM_GOAL: return GOAL;
			case ITM_HEALTH: return HEALTH;
			case ITM_COIN: return COIN;
			case ITM_OBSTACLE1: return OBSTACLE1;
			case ITM_OBSTACLE2: return OBSTACLE2;
			case ITM_ENEMY1: return ENEMY1;
			case ITM_ENEMY2: return ENEMY2;
			case ITM_ENEMY3: return ENEMY3;
			case ITM_ENEMY4: return ENEMY4;
			case ITM_ENEMY5: return ENEMY5;
			case ITM_LIFE: return LIFE;
			case ITM_GAMEOVER: return GAMEOVER;
			case ITM_BOMB:return BOMB;
			case ITM_SLOWDOWN: return SLOWDOWN;

			default: return EMPTY;	// A click on empty place in toolbar
			}
		}

		// [2] User clicks on the grid area
		if ( (y >= ToolBarHeight) && (y < WindHeight - StatusBarHeight))
		{
			return GRID_AREA;	
		}

		// [3] User clicks on the status bar
		return STATUS;
	}
	// ============ GUI in the GAME mode ============
	else	
	{

		char keyData;
		keytype Ktype = pWind->GetKeyPress(keyData);
		//char c = getch();
		//int Ascii = c;
		//if (c == 98)
		//	Ktype = b;
		if(Ktype == ESCAPE )
		{
			pWind->FlushKeyQueue();
			pWind->FlushMouseQueue();
			return PAUSE;
		}

		if (Ktype == ARROW)		//move player using arrow keys
		switch(keyData)
		{
		case 2:	return MOVE_DOWN;
		case 4:	return MOVE_LEFT;
		case 6:	return MOVE_RIGHT;
		case 8:	return MOVE_UP;				
		}

		else if (Ktype == ASCII && (keyData == 'B' || keyData == 'b')) { return Bombenemies; }
		return NO_MOVE; // if other keys is pressed OR if it can't move because of obstacle

		///TODO:
		// perform more checks if needed and return the corresponding ActionType
	}	

}


//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

GUI_MODE GUI::getInterfaceMode() const
{
	return InterfaceMode;
}

void GUI::Converttogame(int t, int w){

	string Mi[5];
	Mi[0] = "images\\cells\\Full Life.jpg";
	Mi[1] = "images\\cells\\Empty Life.jpg";
	Mi[2] = "images\\cells\\BombWeapon.jpg";
	Mi[3] = "images\\cells\\SlowDownWeapon.jpg";
	Mi[4] = "images\\cells\\Blank.jpg";

	for (int i = 0; i < 18; i++){
		pWind->DrawImage(Mi[4], (i)*MenuItemWidth, 0, MenuItemWidth, ToolBarHeight);
	}
	for (int i = 18; i < 18 + t; i++){
		pWind->DrawImage(Mi[0], i*MenuItemWidth, 0, MenuItemWidth, ToolBarHeight);
	}
	for (int i = 18 + t; i < 23; i++){
		pWind->DrawImage(Mi[1], i*MenuItemWidth, 0, MenuItemWidth, ToolBarHeight);
	}

	switch (w){
	case (1) :
		pWind->DrawImage(Mi[2], 16 * MenuItemWidth, 0, MenuItemWidth, ToolBarHeight);
		break;
	case (2) :
		pWind->DrawImage(Mi[3], 17 * MenuItemWidth, 0, MenuItemWidth, ToolBarHeight);
		break;
	case (0) :
		pWind->DrawImage(Mi[4], 16 * MenuItemWidth, 0, MenuItemWidth, ToolBarHeight);
		pWind->DrawImage(Mi[4], 17 * MenuItemWidth, 0, MenuItemWidth, ToolBarHeight);
		break;
	}

	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, ToolBarHeight, WindWidth, ToolBarHeight);

}

void GUI::Converttomenu(){

	string MenuItemImages[MENU_ITM_COUNT];
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\newLoad.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\newSave.jpg";
	MenuItemImages[ITM_START] = "images\\MenuItems\\newStart.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\newExit.jpg";
	MenuItemImages[ITM_STARTPOINT] = "images\\cells\\Start Cell.jpg";
	MenuItemImages[ITM_GOAL] = "images\\cells\\Goal Cell.jpg";
	MenuItemImages[ITM_COIN] = "images\\cells\\Coin.jpg";
	MenuItemImages[ITM_HEALTH] = "images\\cells\\Add Health.jpg";
	MenuItemImages[ITM_OBSTACLE1] = "images\\cells\\Obstacle1.jpg";
	MenuItemImages[ITM_GAMEOVER] = "images\\cells\\Game Over.jpg";
	MenuItemImages[ITM_OBSTACLE2] = "images\\cells\\Obstacle2.jpg";
	MenuItemImages[ITM_ENEMY1] = "images\\cells\\shoe1.jpg";
	MenuItemImages[ITM_ENEMY2] = "images\\cells\\shoe2.jpg";
	MenuItemImages[ITM_ENEMY3] = "images\\cells\\shoe3.jpg";
	MenuItemImages[ITM_ENEMY4] = "images\\cells\\shoe4.jpg";
	MenuItemImages[ITM_ENEMY5] = "images\\cells\\shoe5.jpg";
	MenuItemImages[ITM_LIFE] = "images\\cells\\Full Life.jpg";
	MenuItemImages[ITM_BOMB] = "images\\cells\\BombWeapon.jpg";
	MenuItemImages[ITM_SLOWDOWN] = "images\\cells\\SlowDownWeapon.jpg";
	MenuItemImages[ITM_EMPTY] = "images\\cells\\Empty Cell.jpg";
	MenuItemImages[ITM_PLAYER] = "images\\cells\\player.jpg";

	// Draw menu item one image at a time

	for (int i = 0; i < MENU_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, ToolBarHeight);
	pWind->DrawImage("images\\cells\\Blank.jpg", 21*MenuItemWidth, 0, MenuItemWidth, ToolBarHeight);
}




void GUI::setInterfaceMode(GUI_MODE mode) 
{
	InterfaceMode = mode;
}

////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearStatusBar() const
{
	// Clear Status bar by drawing a filled rectangle with status bar background color
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(10, WindHeight - StatusBarHeight, WindowWidth, WindHeight);
}

void GUI::ClearDynamicStatusBar(int n) const
{
	// Clear Status bar by drawing a filled rectangle with status bar background color
	pWind->SetPen(StatusBarColor, 1);
	pWind->SetBrush(StatusBarColor);
	pWind->DrawRectangle(n, WindHeight - StatusBarHeight, n + 130, WindHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearGridArea() const
{

	
	// Set the pen of the vertical and horizontal lines of the Grid
	pWind->SetPen(GridLineColor,1);
	int x1, y1, x2, y2;

	// Draw Vertical Lines
	y1 = ToolBarHeight;
	y2 = WindHeight - StatusBarHeight;
	for (int i = 0; i < NumColumnCells; i++)
	{
		x1 = x2 = i * GridCellWidth; 
		pWind->DrawLine(x1, y1, x2, y2);
	}	
	
	// Draw Horizontal Lines
	x1 = 0;
	x2 = WindWidth;
	for (int i = 0; i < NumRowCells; i++) 
	{
		y1 = y2 = ToolBarHeight + i * GridCellWidth; 
		pWind->DrawLine(x1, y1, x2, y2);
	}	
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreateMenu() 
{
	InterfaceMode = MODE_MENU;

	// You can draw the tool bar icons in any way you want.
	// Below is one possible way
	
	// First prepare List of images for each menu item
	// To control the order of these images in the menu, 
	// reoder them in UI_Info.h ==> enum MENU_ITEMS
	string MenuItemImages[MENU_ITM_COUNT];
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\newLoad.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\newSave.jpg";
	MenuItemImages[ITM_START] = "images\\MenuItems\\newStart.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\newExit.jpg";
	MenuItemImages[ITM_STARTPOINT] = "images\\cells\\Start Cell.jpg";
	MenuItemImages[ITM_GOAL] = "images\\cells\\Goal Cell.jpg";
	MenuItemImages[ITM_COIN] = "images\\cells\\Coin.jpg";
	MenuItemImages[ITM_HEALTH] = "images\\cells\\Add Health.jpg";
	MenuItemImages[ITM_OBSTACLE1] = "images\\cells\\Obstacle1.jpg";
	MenuItemImages[ITM_GAMEOVER] = "images\\cells\\Game Over.jpg";
	MenuItemImages[ITM_OBSTACLE2] = "images\\cells\\Obstacle2.jpg";
	MenuItemImages[ITM_ENEMY1] = "images\\cells\\shoe1.jpg";
	MenuItemImages[ITM_ENEMY2] = "images\\cells\\shoe2.jpg";
	MenuItemImages[ITM_ENEMY3] = "images\\cells\\shoe3.jpg";
	MenuItemImages[ITM_ENEMY4] = "images\\cells\\shoe4.jpg";
	MenuItemImages[ITM_ENEMY5] = "images\\cells\\shoe5.jpg";
	MenuItemImages[ITM_LIFE] = "images\\cells\\Full Life.jpg";
	MenuItemImages[ITM_BOMB] = "images\\cells\\BombWeapon.jpg";
	MenuItemImages[ITM_SLOWDOWN] = "images\\cells\\SlowDownWeapon.jpg";
	MenuItemImages[ITM_EMPTY] = "images\\cells\\Empty Cell.jpg";
	MenuItemImages[ITM_PLAYER] = "images\\cells\\player.jpg";
	
		// Draw menu item one image at a time
	
		for (int i = 0; i < MENU_ITM_COUNT; i++)
			pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, ToolBarHeight);


	
		// Draw a line under the toolbar
		pWind->SetPen(RED, 3);
		pWind->DrawLine(0, ToolBarHeight, WindWidth, ToolBarHeight);
	}



//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(int b, string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(MsgColor, 50);
	pWind->SetFont(18, BOLD , BY_NAME, "Verdana");   
	pWind->DrawString(b, WindHeight - (int)(StatusBarHeight/1.3), msg);
}

void GUI::PrintDynamicMessage(int b, string msg) const	//Prints a message on status bar
{
	ClearDynamicStatusBar(b);   //First clear the status bar

	pWind->SetPen(NAVYBLUE, 50);
	pWind->SetFont(18, BOLD, BY_NAME, "Verdana");
	pWind->DrawString(b, WindHeight - (int)(StatusBarHeight / 1.3), msg);
}

//======================================================================================//
//						Game Objects Drawing Functions   								//
//======================================================================================//

void GUI::DrawCell(const Cell * cell) const
{
	pWind->SetPen(ObstacleColor, 1);
	pWind->SetBrush(ObstacleColor);
	drawstyle style = FILLED;	

	int x = cell->getCol() * GridCellWidth;
	int y = ToolBarHeight + ( cell->getRow() * GridCellWidth );
	pWind->DrawImage(cell->getImage(),x+1, y+1, GridCellWidth-1, GridCellWidth-1) ;
}



//////////////////////////////////////////////////////////////////////////////////////////




GUI::~GUI()
{
	delete pWind;
}
