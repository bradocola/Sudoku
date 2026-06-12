#include "Player.h"
#include "CardM10.h"
#include "CardM11.h"
#include "CardM12.h"
#include "CardM13.h"
#include "GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;
	this->CanMove = true;
	iced=false; 
	for (int i = 0; i < 4; i++)
	{
		arrFired[i]=0;
		arrpoisoned[i]=0;
		superpowerused[i]=true;
	}
	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;

}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::setIced()
{
	iced = true;
}

void Player::setFired(int n)
{
	arrFired[n] = 3;
}
void Player::setPoisoned(int n)
{
	arrpoisoned[n] = 5;
}
void Player::SetWallet(int wallet)
{
	if (wallet < 0)
	{
		this->wallet = 0;
	}
	else
	{
		this->wallet = wallet;
	}
	// Make any needed validations
}

void Player::DecWalletForSuperPowers()
{
	SetWallet(GetWallet() - 20);
}


void Player::DecTurnCount()
{
	turnCount = GetTurnCount() - 1;
}

void Player::IncTurnCount()
{
	turnCount = GetTurnCount() + 1;
}

int Player::GetWallet() const
{
	return wallet;
}

void Player::MakeCanMoveFalse()
{
	CanMove = false;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

int Player::GetJustRolledDiceNum() const
{
	return justRolledDiceNum;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];

	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);
	///TODO: use the appropriate output function to draw the player with "playerColor"

}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);
	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)

}

// ====== Game Functions ======

void Player::Move(Grid* pGrid, int diceNumber)
{

		///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


		// == Here are some guideline steps (numbered below) to implement this function ==
	
		for (int i = 0; i < 4; i++)
		{
			
			if (arrFired[i] != 0)
			{
				arrFired[i]--;
				DecWalletForSuperPowers();
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (arrpoisoned[i] != 0)
			{
				arrpoisoned[i]--;
				diceNumber--;
			}
		}
		// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
		this->turnCount += 1;
		
		// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
		//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
		Output* pOut=pGrid->GetOutput();
		Input* pIn = pGrid->GetInput();
		bool endcell = 0;
		CellPosition pos(pCell->GetCellPosition());
		
		if (CanMove)
		{
			
			if (turnCount == 3)
			{
				pOut->PrintMessage("Do you wish to launch a special attack instead of recharging ? y / n");
				string buy = pIn->GetSrting(pOut);
				pOut->ClearStatusBar();
				int s = 0;
				for (int i = 0; i < 4; i++)
				{
					if (superpowerused[i] == false)
						s++;
				}
				if ((buy[0] == 'y' || buy[0] == 'Y') && (s != 2))
				{
					bool done = false;

					do{
						pOut->PrintMessage("Choose one of the following: 0 for iced, 1 for fired, 2 for poison, 3 for lightening");
						string choosenPower = pIn->GetSrting(pOut);
						pOut->ClearStatusBar();
						int choosenPlayer;
						if (choosenPower[0] == '0' && superpowerused[0] != false)
						{
							do{
								pOut->PrintMessage("Choose one of the players");
								choosenPlayer = pIn->GetInteger(pOut);
								pOut->ClearStatusBar();
								if (!(choosenPlayer < 4 && choosenPlayer >= 0) || (playerNum == (choosenPlayer)))
								{
									pGrid->PrintErrorMessage("please make sure you have choosen a valid player, Click to continue...");
								}
							} while (!(choosenPlayer < 4 && choosenPlayer >= 0) || (playerNum == (choosenPlayer)));
							pGrid->Icedpower(choosenPlayer);
							superpowerused[0] = false;
							done = true;
						}
						else if (choosenPower[0] == '1' && superpowerused[1] != false)
						{
							do {
								pOut->PrintMessage("Choose one of the players");
								choosenPlayer = pIn->GetInteger(pOut);
								pOut->ClearStatusBar();
								if (!(choosenPlayer < 4 && choosenPlayer >= 0) || (playerNum == choosenPlayer))
								{
									pGrid->PrintErrorMessage("please make sure you have choosen a valid player, Click to continue...");
								}
							} while (!(choosenPlayer < 4 && choosenPlayer >= 0) || (playerNum == choosenPlayer));
							pGrid->Firedpower(choosenPlayer);
							superpowerused[1] = false;
							done = true;
						}
						else if (choosenPower[0] == '2' && superpowerused[2] != false)
						{
							do {
								pOut->PrintMessage("Choose one of the players");
								choosenPlayer = pIn->GetInteger(pOut);
								pOut->ClearStatusBar();
								if (!(choosenPlayer < 4 && choosenPlayer >= 0) || (this->playerNum == choosenPlayer))
								{
									pGrid->PrintErrorMessage("please make sure you have choosen a valid player, Click to continue...");
								}
							} while (!(choosenPlayer < 4 && choosenPlayer >= 0) || (this->playerNum == choosenPlayer));
							pGrid->Poisonedpower(choosenPlayer);
							superpowerused[2] = false;
							done = true;
						}
						else if (choosenPower[0] == '3' && superpowerused[3] != false)
						{
							pGrid->Lightening();
							superpowerused[3] = false;
							done = true;
						}
						else if (!done)
						{
							pGrid->PrintErrorMessage("please make sure you have choosen a valid number and a power differ from the last one, click to continue...");
						}
					} while (!done);
					this->turnCount = 0;
					return;
				}
				else
				{
					this->wallet += diceNumber * 10;
					this->turnCount = 0;
					return;
				}
			}
			else if (iced)
			{
				iced = false;
				return;
			}
			else
			{
				
				// 3- Set the justRolledDiceNum with the passed diceNumber
				this->justRolledDiceNum = diceNumber;

				// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
				//    Using the appropriate function of CellPosition class to update "pos"
				
				if (pos.GetCellNum() + this->justRolledDiceNum > 99)
				{
					endcell = 1;
				}
				pos.AddCellNum(this->justRolledDiceNum);

			}

			// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
			//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position

			pGrid->UpdatePlayerCell(this, pos);

			// 6- Apply() the game object of the reached cell (if any)
			if(turnCount!=3){
				GameObject* obj = pCell->GetGameObject();
				if (pCell->HasLadder())
				{
					obj->Apply(pGrid, this);
				}
				else if (pCell->HasSnake())
				{
					obj->Apply(pGrid, this);
				}
				else if (pCell->HasCard())
				{
					obj->Apply(pGrid, this);
				}
				CellPosition c = pCell->GetCellPosition();
				this->stepCount = c.GetCellNum();
			}
			// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
			if (endcell)// need to handle we don't win in 99 we win in 100
			{
				pGrid->SetEndGame(true);
				pGrid->PrintErrorMessage("Game has ended");
			}
		}else
		{

			if (turnCount == 3)
			{
				this->turnCount = 0;
				return;
			}
			pGrid->UpdatePlayerCell(this, pos);
			pOut->PrintMessage("Can't move or get money you were on card 8");
			CanMove = true;
		}
}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}


void Player::reset(Output* pOut)      //added this function to reset the player
{
	this->ClearDrawing(pOut);
	this->SetWallet(100);
	this->turnCount = 0;
	this->justRolledDiceNum = 0;
	Cell* c = new Cell(8, 0);
	this->SetCell(c);
	this->CanMove = true;
	iced = false;
	for (int i = 0; i < 4; i++)
	{
		arrFired[i] = 0;
		arrpoisoned[i] = 0;
		superpowerused[i] = true;
	}
	this->Draw(pOut);
	CardM10::ResetOwnership();
	CardM11::ResetOwnership();
	CardM12::ResetOwnership();
	CardM13::ResetOwnership();
}