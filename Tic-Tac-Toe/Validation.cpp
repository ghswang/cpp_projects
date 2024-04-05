//
// Validation.cpp
//

#include <algorithm> // std::find
#include <cctype> // isspace
#include <iostream> // std::cout, std::endl
#include <sstream> // std::istringstream

#include "Validation.h"

using namespace std;

bool isGameOver(const Board& game) {
	for (auto& row : game.board) {
		if (find(row.begin(), row.end(), '*') != row.end()) {
			return false;
		}
	}

	return true;
}

bool isUsageInfo(const string& input) {
	unsigned int num_chars = 0;
	bool found_i = false;
	
	for (auto& ch : input) {
		if (isspace(ch)) {
			continue;
		}
		else {
			if (ch == 'i') {
				found_i = true;
			}

			num_chars++;
		}
	}

	if (found_i && num_chars == 1) {
		return true;
	}

	return false;
}

bool isQuit(const string& input) {
	unsigned int num_chars = 0;
	bool found_q = false;
	
	for (auto& ch : input) {
		if (isspace(ch)) {
			continue;
		}
		else {
			if (ch == 'q') {
				found_q = true;
			}

			num_chars++;
		}
	}

	if (found_q && num_chars == 1) {
		return true;
	}

	return false;
}

bool isValidMove(const string& input, const Board& game) {
	return (isValidFormat(input, game) && isInBounds(input, game) && isMoveAvailable(input, game));
}

bool isValidFormat(const string& input, const Board& game) {
	bool foundFirstNum = false, foundSecondNum = false, isFirstNumEnd = false, isSecondNumEnd = false;
	
	for (unsigned short i = 0; i < input.length(); i++) {
		if (isspace(input[i]) && !foundFirstNum) { // ignoring all whitespace preceding first number
			continue;
		}
		else if (isdigit(input[i]) && !isFirstNumEnd) { // found first number
			foundFirstNum = true;
		}
		else if (isspace(input[i]) && foundFirstNum && !foundSecondNum) { // ignoring all whitespace following first number
			isFirstNumEnd = true;
		}
		else if (isdigit(input[i]) && isFirstNumEnd && !isSecondNumEnd) { // found second number
			foundSecondNum = true;
		}
		else if (isspace(input[i]) && foundSecondNum) { // ignoring all whitespace following second number
			isSecondNumEnd = true;
		}
		else if (!isspace(input[i]) && isSecondNumEnd) { // found excess characters (i.e. invalid inputs)
			game.print();
			cout << "Too many arguments entered" << endl;
			return false;
		}
		else if (!isdigit(input[i])) {
			game.print();
			cout << "Please enter only positive integers for the row and the column" << endl;
			return false;
		}
	}

	if (foundFirstNum && foundSecondNum) {
		return true;
	}

	game.print();
	cout << "Too few arguments entered: ";
	if (foundFirstNum) {
		cout << "column number was not specified" << endl;
	}
	else {
		cout << "neither row number nor column number was specified" << endl;
	}
	return false;
}

bool isInBounds(const string& input, const Board& game) {
	unsigned int row, col;
	
	istringstream iss(input);
	iss >> row >> col;

	if (row >= game.getDim() && col >= game.getDim()) {
		game.print();
		cout << "Both the specified row number and column number are too large" << endl;
		return false;
	}
	else if (row >= game.getDim()) {
		game.print();
		cout << "The specified row number is too large" << endl;
		return false;
	}
	else if (col >= game.getDim()) {
		game.print();
		cout << "The specified column number is too large" << endl;
		return false;
	}

	return true;
}

bool isMoveAvailable(const string& input, const Board& game) {
	unsigned int row, col;

	istringstream iss(input);
	iss >> row >> col;

	if (game.board[row][col] == '*') {
		return true;
	}

	game.print();
	cout << "Your specified move is no longer available" << endl;
	return false;
}

bool isWon(const Board& game) {
	return (isWonHorizontally(game) || isWonVertically(game) || isWonDiagonally(game));
}

bool isWonHorizontally(const Board& game) {
	unsigned int consecutive = 1;
	
	for (auto& row : game.board) {
		for (unsigned int j = 1; j < game.getDim(); j++) {
			if (row[0] != '*' && row[j] == row[0]) {
				consecutive++;

				if (consecutive == 3) {
					return true;
				}
			}
			else { // if discrepancy found, immediately move on to checking the next row
				break;
			}
		}

		consecutive = 1; // reset in-a-row count for next row
	}

	return false;
}

bool isWonVertically(const Board& game) {
	unsigned int consecutive = 1;

	for (unsigned int j = 0; j < game.getDim(); j++) {
		for (unsigned int i = 1; i < game.getDim(); i++) {
			if (game.board[0][j] != '*' && game.board[i][j] == game.board[0][j]) {
				consecutive++;

				if (consecutive == 3) {
					return true;
				}
			}
			else { // if discrepancy found, immediately move on to checking the next column
				break;
			}
		}

		consecutive = 1;
	}

	return false;
}

bool isWonDiagonally(const Board& game) {
	return (isWonLeftDiagonal(game) || isWonRightDiagonal(game));
}

bool isWonLeftDiagonal(const Board& game) {
	unsigned int i = game.getDim() - 1, j = 0;

	char top_left = game.board[i--][j++];
	if (top_left == '*') { // guaranteed that left diagonal is not a win
		return false;
	}

	while (i >= 0 && j < game.getDim()) {
		if (game.board[i--][j++] != top_left) {
			return false;
		}
	}
	
	return true;
}

bool isWonRightDiagonal(const Board& game) {
	unsigned int i = 0, j = 0;

	char bottom_right = game.board[i++][j++];
	if (bottom_right == '*') { // guaranteed that right diagonal is not a win
		return false;
	}

	while (i < game.getDim() && j < game.getDim()) {
		if (game.board[i++][j++] != bottom_right) {
			return false;
		}
	}

	return true;
}