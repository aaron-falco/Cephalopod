/*
The game Cephalopodand and its rules were invented by Mark Steere on February 25, 2006. Other games created by Mark Steere can be found at marksteeregames.com
*/
#include<iostream>
#include<time.h>
#include<algorithm>
#include<unordered_map>
#include<sstream>
#include<vector>
#include<set>
#include<queue>
#include<limits>
#include<stdlib.h>

using namespace std;

#include "Cell.h"
#include "Board.h"
#include "Player.h"
#include "CephalopodGame.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "ComputerPlayer.h"
#include "MinMaxPlayer.h"

int main() {
	srand(time(0));

	int p1Wins = 0, p2Wins = 0;

	bool play = true;

	do
	{
		Player* players[2];

		char playType = 'A';

		std::cout << endl << endl << "Please Select Your Game Type: " << endl << endl <<
			"	Human vs MiniMax Player - A" << endl <<
			"	MinMax vs Random Player - B" << endl <<
			"	Random vs Computer Player - C" << endl <<
			"	MinMax vs Computer Player - D" << endl <<
			"	Exit - X" << endl;

		bool validIn;
		do {
			std::cin >> playType;
			validIn = true;
			switch (playType)
			{
			case 'a':
				players[0] = new HumanPlayer(1);
				players[1] = new MinMaxPlayer(-1);

				break;
			case 'A':
				players[0] = new HumanPlayer(1);
				players[1] = new MinMaxPlayer(-1);

				break;

			case 'b':
				players[0] = new MinMaxPlayer(1);
				players[1] = new RandomPlayer(-1);

				break;
			case 'B':
				players[0] = new MinMaxPlayer(1);
				players[1] = new RandomPlayer(-1);

				break;

			case 'c':
				players[0] = new ComputerPlayer(1);
				players[1] = new RandomPlayer(-1);

				break;
			case 'C':
				players[0] = new ComputerPlayer(1);
				players[1] = new RandomPlayer(-1);

				break;

			case 'd':
				players[0] = new MinMaxPlayer(1);
				players[1] = new ComputerPlayer(-1);

				break;
			case 'D':
				players[0] = new MinMaxPlayer(1);
				players[1] = new ComputerPlayer(-1);

				break;
			case 'x':
				play = false;
				continue;
				break;
			case 'X':
				play = false;
				break;
			default:
				std::cout << endl << "Invalid Selection" << endl;
				validIn = false;
				continue;
			}
		} while (!validIn);

		if (!play) break;


		int row = 0, col = 0;
		char inp[] = "";
		char* pEnd;
		while (row == 0) {
			std::cout << "Input number of rows for the board (between 2 & 10):";
			cin >> inp;
			if (!isdigit(inp[0])) {
				cout << endl << "Invalid Entry" << endl;
				continue;
			}
			row = strtol(inp, &pEnd, 10);
			if (row < 1 || row > 10) {
				cout << endl << "Invalid Entry" << endl;
				row = 0;
			}
		}
		while (col == 0) {
			std::cout << "Input number of columns for the board (between 2 & 10):";
			cin >> inp;
			if(!isdigit(inp[0])) {
				cout << endl << "Invalid Entry" << endl;
				continue;
			}
			col = strtol(inp, &pEnd, 10);
			if (col < 1 || col > 10) {
				cout << endl << "Invalid Entry" << endl;
				row = 0;
			}
		}
		//cin >> row >> col;

		Board board(row, col);
		CephalopodGame game(board, players);
		int winner = game.play();

		if (winner == 1) {
			p1Wins++;
		}
		else if (winner == -1)
		{
			p2Wins++;
		}


		delete players[0];
		delete players[1];

	} while (play);



	std::cout << endl << "Player 1 won " << p1Wins << " times." << endl;
	std::cout << endl << "Player 2 won " << p2Wins << " times." << endl;

	return 0;
}
