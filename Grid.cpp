#include "Grid.h"

#include "Cell.h"

Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	Path = "";
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
			CellAns[i][j] = new int(0);
		}
	}
}

// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetPath(string path)
{
	Path = path;
}

string Grid::GetPath() const
{
	return Path;
}

void Grid::SetCellValue(int row, int col, int val, bool isGiven) {
	CellList[row][col]->SetValue(val);
	CellList[row][col]->SetGiven(isGiven);
}

void Grid::SetSelectedCell(CellPosition pos) {
	selectedCell = pos;
}

bool Grid::IsCellGiven(int row, int col) const {
	return CellList[row][col]->IsGiven();
}

int Grid::GetCellValue(int row, int col) const {
	return CellList[row][col]->GetValue();
}

void Grid::ClearBoard()
{
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			CellList[i][j]->Clear();
		}
	}
	selectedCell = CellPosition(-1, -1);
}

void Grid::SetCellAns(int row, int col, int val) {
	*CellAns[row][col] = val;
}



// =============== SUDOKU =====================

bool Grid::isValidSudoku() {
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (*CellAns[i][j] != CellList[i][j]->GetValue()&& CellList[i][j]->IsGiven()) {
				return false;
			}
		}
	}
	return true;
}


// ========= User Interface Functions =========

void Grid::UpdateInterface() const
{
	pOut->ClearGridArea();
	// 1- Draw cells with or without cards 
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // left to right
		{
			CellPosition currentPos(i, j);
			bool isSelected = (currentPos.VCell() == selectedCell.VCell() && currentPos.HCell() == selectedCell.HCell());
			pOut->DrawCell(currentPos, CellList[i][j]->GetValue(), CellList[i][j]->IsGiven(), isSelected);
		}
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}

Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
			delete CellAns[i][j];
		}
	}
}