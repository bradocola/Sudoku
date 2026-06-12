#include "NewGame.h"
#include "Grid.h"
#include <fstream>

NewGame::NewGame(ApplicationManager* pApp) : Action(pApp)
{

}

void NewGame::ReadActionParameters()
{

}

void NewGame::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pGrid->ClearBoard();

	pOut->PrintMessage("Select Difficulty: Enter 1 (Easy), 2 (Medium), or 3 (Hard)");
	int diff = pIn->GetInteger(pOut);

	pOut->PrintMessage("Select Level from 1 to 9");
	int level = pIn->GetInteger(pOut);

	string filePath = "";
	if (level > 0 && level <= 9) {
		switch (diff) {
		case 1:
			filePath = "Levels\\Easy\\level";
			filePath += to_string(level);
			filePath += ".txt";
			break;
		case 2:
			filePath = "Levels\\Medium\\level";
			filePath += to_string(level);
			filePath += ".txt";
			break;
		case 3:
			filePath = "Levels\\Hard\\level";
			filePath += to_string(level);
			filePath += ".txt";
			break;
		default:
			pOut->PrintMessage("Invalid choice. Defaulting to Easy (Level 1).");
			filePath = "Levels\\Easy\\level1.txt";
		}
	}
	else
		{
		pOut->PrintMessage("Invalid level. Defaulting to Level 1.");
		filePath = "Levels\\Easy\\level1.txt";
	}

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
	string dummy;
	while (infile >> dummy && dummy != "Solution");

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (infile >> val)
			{
				if (val != 0)
				{
					pGrid->SetCellAns(i, j, val);
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
	pOut->PrintMessage("Level loaded successfully!");
	pGrid->SetPath(filePath);
}

NewGame::~NewGame()
{

}