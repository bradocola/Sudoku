#pragma once
#include "Action.h"
class SelectCell : public Action
{
public:
    SelectCell(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
};
