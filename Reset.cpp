#include "Reset.h"
#include "ApplicationManager.h"
#include "Grid.h"

Reset::Reset(ApplicationManager* pApp) : Action(pApp)
{
	F = "";
}
void Reset::ReadActionParameters() {}

void Reset::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pGrid->ClearBoard();

	string filePath = pGrid->GetPath();

	ifstream infile(filePath);
	int val;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (infile >> val)
			{
				if (val != 0)
				{
					pGrid->SetCellValue(i, j, val, true);
				}
			}
			else
			{
				pGrid->PrintErrorMessage("Error: Corrupted level file format!");
				infile.close();
				return;
			}
		}
	}
	infile.close();
	pOut->PrintMessage("Level Restored successfully!");
}

Reset::~Reset() {}