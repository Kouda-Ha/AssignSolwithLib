#include "stdafx.h"
#include "std_lib_facilities.h"	// get the facilities for this course
#include <vector>
#include "NandC.h"

using namespace System;

int main(cli::array<System::String ^> ^args)
{
	NandC nandc;

	cout << "Play noughts and crosses... \n";
	cout << "O goes first, specify a square by stating the (row column) numbers. \n";
	cout << "The top left square is (1 1)! \n";



	bool check;
	do {
		cout << "Press 's' for a single player game, 't' for a two-player game. \n";
		char type;
		cin >> type;
		check = nandc.setType(type);
	} while (!check);


	cout << "Initial situation: \n";
	nandc.printGame();
	while (nandc.notFinished())
	{

		int r, c;
		do {
			cout << "Input row and column for O \n";
			cin >> r >> c;
			check = nandc.setO(r, c);
		} while (!check);


		cout << "Current situation: \n";
		nandc.printGame();

		if (nandc.notFinished())
		{
			if (nandc.isSinglePlayer())
			{
				cout << "Computer's choice...\n";
				nandc.computerX();
			}
			else {
				do {
					cout << "Input row and column for X \n";
					cin >> r >> c;
					check = nandc.setX(r, c);
				} while (!check);
			}

			cout << "Current situation: \n";
			nandc.printGame();
		}


	}
	cout << "O.K., that game was won by " << nandc.whoWon() << " in " << nandc.numGoes() << " turns. \n";

}