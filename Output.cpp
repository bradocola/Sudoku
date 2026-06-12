#include "Output.h"

#include "Input.h"

////////////////////////////////////////////////////////////////////////////////////////// 

Output::Output()
{
	// Initialize user interface parameters
	UI.InterfaceMode = MODE_PLAY;

	// Widths and Heights

	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 55;
	UI.MenuItemWidth = 55;

	UI.width = 810; // make it divisible by NumHorizontalCells
	UI.height = 810+105;
	UI.wx = 150;
	UI.wy = 150;

	UI.CellWidth = UI.width / NumHorizontalCells;
	UI.CellHeight = (UI.height - UI.ToolBarHeight - UI.StatusBarHeight) / NumVerticalCells;

	// Pen Colors of messages of status bar and players' info
	UI.MsgColor = BLACK;
	UI.GridLineColor = MIDNIGHTBLUE;
	UI.BlockLineColor = WHITE;
	UI.BlockLineWidth = 6;

	UI.CellColor_N = DARKSLATEBLUE;
	UI.CellColor_S = LIGHTBLUE;
	UI.ClueNumColor = BLACK;
	UI.UserNumColor = CYAN;
	UI.FontSize = 36;

	UI.ToolBarColor = BLACK;
	UI.StatusBarColor = BLACK;

	// Create the output window
	pWind = CreateWind(UI.width + 23, UI.height, UI.wx, UI.wy);
	pWind->ChangeTitle("Sudoku Grid Solver");

	pWind->SetPen(BLACK, 1);
	pWind->SetBrush(BLACK);
	pWind->DrawRectangle(0, 0, UI.width + 23, UI.height);

	CreateToolBar();
	ClearGridArea();
	ClearStatusBar();

}

window* Output::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	return pW;
}

Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Some Utility Functions										//
//======================================================================================//

int Output::GetCellStartX(const CellPosition& cellPos) const
{
	return cellPos.HCell() * UI.CellWidth;
}

//////////////////////////////////////////////////////////////////////////////////////////

int Output::GetCellStartY(const CellPosition& cellPos) const
{
	return cellPos.VCell() * UI.CellHeight + UI.ToolBarHeight;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

void Output::ClearStatusBar() const
{
	// Clear drawing a rectangle filled with statusbar background color
	pWind->SetPen(LIGHTGRAY, 1);
	pWind->SetBrush(LIGHTGRAY);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearGridArea() const//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
	// Draw each cell in the Grid: ( NumVerticalCells * NumberHorizontalCells )
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			CellPosition cellPos(i, j);
		}
	}

}

void Output::CreateToolBar() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

	string MenuItemImages[TOOL_ITEM_COUNT];
	MenuItemImages[ITM_NEW] = "images\\sudoku_new.jpg";
	MenuItemImages[ITM_RESET] = "images\\sudoku_reset.jpg";
	MenuItemImages[ITM_EXIT] = "images\\sudoku_exit.jpg";

	for (int i = 0; i < TOOL_ITEM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	
	pWind->SetPen(UI.MsgColor);
	pWind->SetFont(18, BOLD, BY_NAME, "Verdana");
	pWind->DrawString(15, UI.height - (int)(UI.StatusBarHeight / 1.3), msg);
}


void Output::DrawCell(const CellPosition& cellPos, int value, bool isGiven, bool isSelected) const
{
	int cellStartX = GetCellStartX(cellPos);
	int cellStartY = GetCellStartY(cellPos);

	// ----- 1- Draw the cell itself (background) --> Filled Rectangle -----
	pWind->SetPen(UI.GridLineColor, 1);
	pWind->DrawRectangle(cellStartX, cellStartY, cellStartX + UI.CellWidth, cellStartY + UI.CellHeight);

	if (value > 0 && value <= 9)
	{
		pWind->SetPen(isGiven ? UI.ClueNumColor : UI.UserNumColor);
		pWind->SetFont(UI.FontSize, BOLD, BY_NAME, "Arial");
		int w = 0, h = 0;
		pWind->GetIntegerSize(w, h, value);

		// Center the text inside the cell
		int x = cellStartX + (UI.CellWidth - w) / 2;
		int y = cellStartY + (UI.CellHeight - h) / 2;
		pWind->DrawInteger(x, y, value);
	}


}

Output::~Output()
{
	delete pWind;
}

