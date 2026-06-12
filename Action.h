#pragma once

#include "ApplicationManager.h"
#include "Cell.h"

// Base class for all possible actions (actions are icons of the toolbar)
class Action
{
protected:

	ApplicationManager *pManager;
public:

	Action(ApplicationManager *pApp);
	virtual void ReadActionParameters() = 0;
	virtual void Execute() = 0;
	virtual ~Action();
};

