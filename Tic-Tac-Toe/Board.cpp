//
// Board.cpp
//

#include <iostream> // std::cout, std::endl

#include "Board.h"

using namespace std;

Board::Board(void) : dim(3) {
	board = vector<vector<char>>(dim, vector<char>(dim, '*'));
}

void Board::print(void) const {
	std::cout << std::endl;
	
	for (unsigned int i = dim - 1; i >= 0; i--) {
		std::cout << i << " ";
		
		for (unsigned int j = 0; j < dim; j++) {
			std::cout << board[i][j] << " ";
		}
		
		std::cout << std::endl;

		if (i == 0) {
			break;
		}
	}

	std::cout << "  ";

	for (unsigned int j = 0; j < dim; j++) {
		std::cout << j << " ";
	}

	std::cout << std::endl << std::endl;
}

const unsigned int Board::getDim(void) const { return dim; }

void makeMove(Board& game, const unsigned int& row, const unsigned int& col, const char& piece) {
	game.board[row][col] = piece;
}