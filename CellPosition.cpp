#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum);
}

bool CellPosition::SetVCell(int v)
{
	if ((v >= 0) && (v <= 8))
	{
		vCell = v;
		return true;
	}
	return false;
}

bool CellPosition::SetHCell(int h)
{
	if ((h >= 0) && (h <= 8))
	{
		hCell = h;
		return true;
	}
	return false;
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{

	if ((hCell >= 0) && (hCell <= 8) && (vCell >= 0) && (vCell <= 8))
	{
		return true;
	}
	return false;
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this);
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	int NumFromPosition = 1 + cellPosition.HCell() + ((8 - cellPosition.VCell()) * 9);
	return NumFromPosition; 
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	CellPosition position;
	if (cellNum >= 1 && cellNum <= 81)
	{
		int hh = ((cellNum - 1) % 9);
		position.SetHCell(hh);
		int vv = (8 - ((cellNum - 1) / 9));
		position.SetVCell(vv);
	}
	return position;
}
