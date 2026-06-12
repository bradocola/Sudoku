#include "SelectCell.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include <iostream>
using namespace std;

SelectCell::SelectCell(ApplicationManager* pApp) : Action(pApp) {}

void SelectCell::ReadActionParameters() {}

void SelectCell::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	if (pGrid->GetPath().empty()) {
		pOut->PrintMessage("Please select a difficulty and start a New Game first!");
		return;
	}

	CellPosition clickedPos = pIn->GetCellClicked();

	if (clickedPos.IsValidCell()) {
		int r = clickedPos.VCell();
		int c = clickedPos.HCell();
		//AI had helped here
		// 1. Check if the cell is an immutable starting clue
		if (pGrid->IsCellGiven(r, c)) {
			pOut->PrintMessage("Error: Cannot edit starting clues!");
			return;
		}

		// 2. Select and highlight the cell
		pGrid->SetSelectedCell(clickedPos);
		pManager->UpdateInterface(); 

		// 3. Wait for the user to press a keyboard number (1-9 or Backspace/0 to clear)
		int num = pIn->GetNumberPressed();

		if (num >= 0) { 
			// 4. Update the cell value in the grid
			pGrid->SetCellValue(r, c, num, true); 
			pManager->UpdateInterface(); 

			// 5. Run the automatic validation check using isValidSudoku
			if (pGrid->isValidSudoku()) {
				// Check if the board is fully completed (no empty cells left)
				bool isComplete = true;
				for (int i = 0; i < 9; i++) {
					for (int j = 0; j < 9; j++) {
						if (pGrid->GetCellValue(i, j) == 0) {
							isComplete = false;
							break;
						}
					}
					if (!isComplete) break;
				}

				if (isComplete) {
					cout << "you win" << endl;
					pOut->PrintMessage("Congratulations! You Win!");
				} else {
					pOut->PrintMessage("Number placed. No conflicts.");
				}
			} else {
				pOut->PrintMessage("Conflict detected! This placement violates Sudoku rules.");
				pGrid->SetCellValue(r, c, 0, false);
				pManager->UpdateInterface();
			}
		}
	}
}