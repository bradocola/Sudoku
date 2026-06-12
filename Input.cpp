#include "Input.h"

#include "Output.h"

//======================================================================================//
//								General Functions									    //
//======================================================================================//

Input::Input(window* pW)
{
	pWind = pW; 
	lastX = -1;
	lastY = -1;
}


void Input::GetPointClicked(int& x, int& y) const
{
	pWind->FlushMouseQueue();
	pWind->WaitMouseClick(x, y);
}

string Input::GetSrting(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{

		pWind->FlushKeyQueue();
		pWind->WaitKeyPress(Key);
		if (Key == 27)	// ESCAPE key is pressed
			return "";	// returns nothing as user has cancelled label
		if (Key == 13)	// ENTER key is pressed
		{
			pWind->FlushMouseQueue();//stopping mouse inaccurate states
			return Label;
		}
		if ((Key == 8) && (Label.size() >= 1))	// BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////// 

int Input::GetInteger(Output* pO) const
{
	string snum = GetSrting(pO);
	if (snum.empty())
		return -1;

	int l = snum.size();

	for (int i = 0; i < l; i++)
		if (snum[i] < '0' || snum[i] > '9')
			return -1;

	return stoi(snum);
}


//======================================================================================//
//								Game  Functions									        //
//======================================================================================//

ActionType Input::GetUserAction() const
{
	int x = -1, y = -1;
	GetPointClicked(x, y);
	lastX = x;
	lastY = y;

	if (y >= 0 && y < UI.ToolBarHeight)
	{
		int ClickedItemOrder = (x / UI.MenuItemWidth);
		switch (ClickedItemOrder)
		{
		case ITM_NEW: return NEW_GAME;
		case ITM_RESET: return RESET;
		case ITM_EXIT: return EXIT;
		default: return EMPTY;
		}
	}
	if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		return GRID_AREA;

	return STATUS;

}

////////////////////////////////////////////////////////////////////////////////////////// 

CellPosition Input::GetCellClicked() const
{
	CellPosition cellPos;
	if (lastY >= UI.ToolBarHeight && lastY <= (UI.height - UI.StatusBarHeight))
	{
		int x = lastX / UI.CellWidth;
		int y = (lastY - UI.ToolBarHeight) / UI.CellHeight;
		cellPos.SetHCell(x);
		cellPos.SetVCell(y);
	}
	return cellPos;
}

////////////////////////////////////////////////////////////////////////////////////////// 


int Input::GetNumberPressed() const
{
	char key;
	pWind->FlushKeyQueue();
	pWind->WaitKeyPress(key);
	if (key >= '1' && key <= '9')
		return key - '0';

	if (key == 8 || key == 127 || key == '0' || key == ' ')
		return 0;
	return -1; // Indicates an invalid or non-numeric key was pressed
}