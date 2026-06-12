#ifndef UI_INFO_H
#define UI_INFO_H

#include "CMUgraphicsLib\CMUgraphics.h"

#define NumHorizontalCells 9
#define NumVerticalCells 9

enum GUI_MODE
{
	MODE_PLAY
};

enum TOOL_ITEMS
{
	ITM_NEW,
	ITM_RESET,
	ITM_EXIT,

	TOOL_ITEM_COUNT
};

__declspec(selectany) // This line to prevent "redefinition error"

struct UI_Info	// User Interface Info.
{
	GUI_MODE InterfaceMode;

	int	width, height,			// Window width and height
		wx, wy,				// Window starting coordinates
		StatusBarHeight,		// Status Bar Height
		ToolBarHeight,			// Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;			// Width of each item in toolbar menu

	int CellHeight;				// Height of 1 CELL
	int CellWidth;				// Width of 1 CELL

	color MsgColor;             // Color of status bar messages
	color GridLineColor;        // Color of cell borders

	color BlockLineColor;       // Color of thick 3x3 block borders
	int BlockLineWidth;         // Width of thick lines

	color CellColor_N;			// Normal cell background
	color CellColor_S;			// Selected cell background highlight

	color ClueNumColor;         // Text color for original puzzle clues
	color UserNumColor;         // Text color for user-entered numbers
	int FontSize;               // Font size of numbers

	color ToolBarColor;         // Background color of the toolbar
	color StatusBarColor;       // Background color of the status bar

} UI;	// create a global object UI

#endif