#ifndef INPUT_H
#define INPUT_H

#include "DEFS.h"
#include "UI_Info.h" 
#include "CMUgraphicsLib\CMUgraphics.h"
#include "CellPosition.h"
#include <string>
#include <climits>
using namespace std;
class Output;  

class Input
{
private:
	window *pWind;
	int lastX, lastY;
public:
	Input(window *pW);
	void GetPointClicked(int &x, int &y) const;
	string GetSrting(Output* pO) const;
	int GetInteger(Output* pO) const;
	ActionType GetUserAction() const;
	CellPosition GetCellClicked() const;
	int GetNumberPressed() const;
};

#endif