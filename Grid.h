#pragma once

#include "UI_Info.h"
#include "DEFS.h"

#include "Input.h"
#include "Output.h"
#include "Cell.h"
#include <fstream>
#include <vector>
// forward declarations (the includes are in the cpp)
class Cell;

class Grid
{
	Output * pOut;   // A pointer to the Output object
	Input * pIn;     // A pointer to the Input object

	Cell * CellList[NumVerticalCells][NumHorizontalCells];
	int * CellAns[NumVerticalCells][NumHorizontalCells];
	CellPosition selectedCell;
	string Path;

public:

	Grid(Input * pIn, Output * pOut);
	// ========= Setters and Getters Functions =========

	Input * GetInput() const;	// Gets a Pointer to the Input
	Output * GetOutput() const; // Gets a Pointer to the Output 

	void ClearBoard();

	void UpdateInterface() const;
	void PrintErrorMessage(string msg);
	void SetPath(string path);
	string GetPath() const;
	bool IsCellGiven(int row, int col) const;
	int GetCellValue(int row, int col) const;
	void SetCellValue(int row, int col, int val, bool isGiven);
	void SetCellAns(int row, int col, int val);
	void SetSelectedCell(CellPosition pos);
	bool isValidSudoku();

	~Grid();
};

