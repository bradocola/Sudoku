#ifndef OUPTUT_H
#define OUPTUT_H

#include "DEFS.h"
#include "UI_Info.h" 
#include "CMUgraphicsLib\CMUgraphics.h"
#include "CellPosition.h"
#include <string>
#include <climits>
using namespace std;

// forward declarations (their includes are in the cpp)
class Input;

class Output	// The application manager & grid (phase 2) should have a pointer to this class
{
private:

	window* pWind;
	int GetCellStartX(const CellPosition& cellpos) const;
	int GetCellStartY(const CellPosition& cellpos) const;
public:

	Output();
	window* CreateWind(int, int, int, int) const;
	Input* CreateInput() const;

	void ClearStatusBar() const;
	void ClearGridArea() const;
	void CreateToolBar() const;
	void PrintMessage(string msg) const;	
	void DrawCell(const CellPosition& cellpos, int value, bool isGiven, bool isSelected = false) const;

	~Output();
};

#endif