#pragma once

class CellPosition
{
	int vCell; // the vertical cell number: starts from 0 to NumVerticalCells - 1
	int hCell; // the horizontal cell number: starts from 0 to NumHorizontalCells - 1

public:
	CellPosition ();
	CellPosition (int v, int h);
	CellPosition (int cellNum);
	bool SetVCell(int v);
	bool SetHCell(int h);
	int VCell() const;
	int HCell() const;
	bool IsValidCell() const;
	int GetCellNum() const;
	static int GetCellNumFromPosition(const CellPosition & cellPosition);
	static CellPosition GetCellPositionFromNum(int cellNum);
};

