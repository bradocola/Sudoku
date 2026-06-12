#pragma once 

#include "UI_Info.h"
#include "CellPosition.h"

// Class forward declarations (their #include is in the .cpp file)
class Grid;
class Output;

class Cell
{
	const CellPosition position;
	int value;
	bool isGiven;
public:
	Cell(const CellPosition & pos);
	Cell(int v, int h);
	CellPosition GetCellPosition() const;

	void SetValue(int val);
	int GetValue() const;
	// ======= Setters and Getters Functions ======= 
	void SetGiven(bool given);
	bool IsGiven() const;
	void Clear();
};

