//
// main.cpp
//

#include <iostream> // std::cout, std::cin, std::endl
#include <algorithm> // std::find
#include <cctype> // isspace
#include <sstream> // std::istringstream
#include <ctime> // time
#include <cstdlib> // srand, rand

#include "Validation.h"

using namespace std;

void greeting(void) {
	cout << "\nWelcome to Tic-Tac-Toe!" << endl << endl;
	cout << "First to three-in-a-row wins!" << endl;
	cout << "Player 1 is 'X' and Player 2 is 'O'!" << endl;
	cout << "Player 1 goes first!" << endl;
}

void moveUsageInfo(void) {
	cout << "\nUsage: row column (e.g. 2 1)" << endl;
}

int main() {
	srand(time(0));
	greeting();

	Board game;
	game.print();

	string input;
	unsigned int row, col;
	bool isPlayerOneTurn = true;

	while (!isGameOver(game)) {
		if (isPlayerOneTurn) {
			cout << "Player 1, please enter your move (type i for usage info | type q to quit the game): ";
			getline(cin, input);

			if (isUsageInfo(input)) {
				moveUsageInfo();
			}
			else if (isQuit(input)) {
				exit(0);
			}

			while (!isValidMove(input, game)) {
				cout << "Player 1, please enter your move (type i for usage info | type q to quit the game): ";
				getline(cin, input);

				if (isUsageInfo(input)) {
					moveUsageInfo();
				}
				else if (isQuit(input)) {
					exit(0);
				}
			}

			istringstream iss(input);
			iss >> row >> col;

			makeMove(game, row, col, 'X');
			game.print();

			isPlayerOneTurn = false;

			if (isWon(game)) {
				cout << "Player 1 has won!" << endl;

				unsigned int n = rand();
				if (n % 5 == 0) {
					cout << "Congratulations! :)" << endl << endl;
				}
				else if (n % 5 == 1) {
					cout << "Great job! :)" << endl << endl;
				}
				else if (n % 5 == 2) {
					cout << "Excellent work! :)" << endl << endl;
				}
				else if (n % 5 == 3) {
					cout << "Outstanding performance! :)" << endl << endl;
				}
				else {
					cout << "Spectacular stuff! :)" << endl << endl;
				}

				return 0;
			}
		}
		else {
			cout << "Player 2, please enter your move (type i for usage info | type q to quit the game): ";
			getline(cin, input);

			if (isUsageInfo(input)) {
				moveUsageInfo();
			}
			else if (isQuit(input)) {
				exit(0);
			}

			while (!isValidMove(input, game)) {
				cout << "Player 2, please enter your move (type i for usage info | type q to quit the game): ";
				getline(cin, input);
				

				if (isUsageInfo(input)) {
					moveUsageInfo();
				}
				else if (isQuit(input)) {
					exit(0);
				}
			}

			istringstream iss(input);
			iss >> row >> col;

			makeMove(game, row, col, 'O');
			game.print();

			isPlayerOneTurn = true;

			if (isWon(game)) {
				cout << "Player 2 has won!" << endl;

				unsigned int n = rand();
				if (n % 5 == 0) {
					cout << "Congratulations! :)" << endl << endl;
				}
				else if (n % 5 == 1) {
					cout << "Great job! :)" << endl << endl;
				}
				else if (n % 5 == 2) {
					cout << "Excellent work! :)" << endl << endl;
				}
				else if (n % 5 == 3) {
					cout << "Outstanding performance! :)" << endl << endl;
				}
				else {
					cout << "Spectacular stuff! :)" << endl << endl;
				}

				return 0;
			}
		}
	}

	cout << "Tie game!" << endl << endl; // will only get here if neither player manages to win
											// (i.e. before all spots are taken on the game board)
}