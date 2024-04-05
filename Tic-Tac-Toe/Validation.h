//
// Validation.h
//

#ifndef VALIDATION_H
	#define VALIDATION_H

	#include <string> // std::string, std::getline

	#include "Board.h"

	bool isGameOver(const Board& game);
	bool isUsageInfo(const std::string& input);
	bool isQuit(const std::string& input);
	bool isValidMove(const std::string& input, const Board& game);
	bool isValidFormat(const std::string& input, const Board& game);
	bool isInBounds(const std::string& input, const Board& game);
	bool isMoveAvailable(const std::string& input, const Board& game);
	bool isWon(const Board& game);
	bool isWonHorizontally(const Board& game);
	bool isWonVertically(const Board& game);
	bool isWonDiagonally(const Board& game);
	bool isWonLeftDiagonal(const Board& game);
	bool isWonRightDiagonal(const Board& game);
#endif