//
// Board.h
//

#ifndef BOARD_H
	#define BOARD_H

	#include <vector> // std::vector

	class Board {
		public:
			std::vector<std::vector<char>> board;
			Board(void);
			void print(void) const;
			const unsigned int getDim(void) const;
		private:
			const unsigned int dim;
	};

	void makeMove(Board& game, const unsigned int& row, const unsigned int& col, const char& piece);
#endif