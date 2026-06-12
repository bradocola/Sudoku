#include "Cell.h"

#include "Grid.h"


Cell::Cell(const CellPosition & pos) : position(pos)
{
	value = 0;
	isGiven = false;
}

Cell::Cell(int v, int h) : position(v, h)
{
	value = 0;
	isGiven = false;
}

CellPosition Cell::GetCellPosition() const
{
	return position;
}

void Cell::SetValue(int v) {
	value = v;
}

void Cell::SetGiven(bool g) {
	isGiven = g;
}

int Cell::GetValue() const {
	return value;
}

bool Cell::IsGiven() const {
	return isGiven;
}

void Cell::Clear() {
	isGiven = false;
	value = 0;
}