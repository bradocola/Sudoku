#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"


class Reset : public Action
{
private:
	string F;
public:
	Reset(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~Reset();
};