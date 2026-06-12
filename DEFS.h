#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"
enum ActionType // The actions supported (add more as needed)
{
	NEW_GAME,			// Clear all and load a new Sudoku puzzle
	RESET,				// Clear user numbers but keep the puzzle clues
	SOLVE,				// Run the auto-solver on the board
	CHECK,				// Validate the board against Sudoku rules
	SAVE_GAME,			// Save grid state to file
	LOAD_GAME,			// Load grid state from file
	EXIT,				// Exit applicatio
	EMPTY,				// Empty Area in ToolBar (NOT inside any action icon)
	GRID_AREA,			// Inside Grid Area
	STATUS 				// Inside StatusBar Area
};

#endif