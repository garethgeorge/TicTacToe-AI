#ifndef __CHESSBOARD_H_
#define __CHESSBOARD_H_

#include <cstdint>
#include <string>

#define BOARD_SIZE 9
#define PLAYER_O -1
#define PLAYER_X 1


typedef int8_t piece;


class TTTMove;

class TTTBoard {
friend class TTTMove;
protected:
	piece spaces[BOARD_SIZE];
public:
	TTTBoard();
	~TTTBoard();

	class MoveIterator {
	private:
		const TTTBoard* board;
		piece player;
		int index;
	public:
		MoveIterator(const TTTBoard* board, piece player);
		bool getNext(TTTMove& m);
	};

	int heuristic(piece curPlayer);

	int minimax(piece player1, piece player2, TTTMove& bestMove);

	bool isGameOver();

	std::string toString();
};

class TTTMove {
private:
	unsigned char index;
	piece p;
public:
	TTTMove() { }
	TTTMove(int index, piece p) {
		this->index = index;
		this->p = p;
	}

	// apply and revert are in fact the same functions!
	inline void apply(TTTBoard& board) {
		piece toSet = p;
		p = board.spaces[index];
		board.spaces[index] = toSet;
	}

	inline void revert(TTTBoard& board) {
		apply(board);
	}

	TTTMove& operator=(const TTTMove& other) {
		index = other.index;
		p = other.p;

		return *this;
	}

	std::string toString();
};

#endif