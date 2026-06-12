#include "ApplicationManager.h"

#include "Grid.h"
#include "NewGame.h"
#include "Reset.h"
#include "SelectCell.h"

ApplicationManager::ApplicationManager()
{
	// Create Input, output and Grid
	pOut = new Output();
	pIn = pOut->CreateInput();
	pGrid = new Grid(pIn, pOut);
}

ApplicationManager::~ApplicationManager()
{
	delete pGrid;
}

Grid* ApplicationManager::GetGrid() const
{
	return pGrid;
}

void ApplicationManager::UpdateInterface() const
{
	pGrid->UpdateInterface();
}

ActionType ApplicationManager::GetUserAction() const
{
	return pIn->GetUserAction();
}

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{

	case NEW_GAME:
		pAct = new NewGame(this);//////////////////////////
		break;
	case RESET :
		pAct = new Reset(this);////////////////////////
		break;
	case GRID_AREA:
		pAct = new SelectCell(this);
		break;
	case EXIT:
		break;
	case STATUS:
		return;
	}

	if (pAct != NULL)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
