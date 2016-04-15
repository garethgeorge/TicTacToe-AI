#include "board.h"
#include <iostream>
#include <climits>
#include <sstream>


TTTBoard::TTTBoard() {
	for (int i = 0; i < BOARD_SIZE; ++i) spaces[i] = 0;
}

TTTBoard::~TTTBoard() {

}

TTTBoard::MoveIterator::MoveIterator(const TTTBoard* board, piece player) : board(board), player(player), index(0) { }

bool TTTBoard::MoveIterator::getNext(TTTMove& m) {
	while (index < BOARD_SIZE) {		
		if (board->spaces[index++] == 0) {
			m = TTTMove(index - 1, player);
			return true;
		}
	}
	return false;
}


int TTTBoard::heuristic(piece curPlayer) {


	if (spaces[0] != 0 && spaces[0] == spaces[4] && spaces[0] == spaces[8])
		return curPlayer == spaces[0] ? 10 : -10;
	if (spaces[2] != 0 && spaces[2] == spaces[4] && spaces[2] == spaces[6])
		return curPlayer == spaces[2] ? 10 : -10;

	for (int i = 0; i < 3; ++i) {
		if (spaces[i] != 0 && spaces[i] == spaces[i+3] && spaces[i] == spaces[i+6])
			return curPlayer == spaces[i] ? 10 : -10;
		if (spaces[3*i] != 0 && spaces[3*i] == spaces[3*i+1] && spaces[3*i] == spaces[3*i+2])
			return curPlayer == spaces[i] ? 10 : -10;
	}

	return 0;
}

bool TTTBoard::isGameOver() {
	int score = heuristic(0);
	if (score == -10)
		return true;
	for (int i = 0; i < BOARD_SIZE; ++i)
		if (spaces[i] == 0)
			return false;
	return true;
}

int TTTBoard::minimax(piece me, piece activeTurn, TTTMove& bestMove) {
	if (isGameOver())
		return heuristic(me);

	int scoreMultiplier = activeTurn == me ? 1 : -1;

	// we are maximizing!
	piece otherPlayer = activeTurn == PLAYER_O ? PLAYER_X : PLAYER_O;

	int max = INT_MIN;
	TTTMove move;
	TTTMove trash;

	MoveIterator mIter(this, activeTurn);

	while (mIter.getNext(move)) {

		move.apply(*this);
		int score = minimax(me, otherPlayer, trash) * scoreMultiplier;
		move.revert(*this);

		if (score > max) {
			max = score;
			bestMove = move;
		}
	}

	return max * scoreMultiplier;
}

std::string TTTBoard::toString() {
	std::stringstream ss;
	for (int i = 0; i < 9;) {
		for (int j = i + 3; i < j; ++i) {
			if (spaces[i] == PLAYER_O)
				ss << "O";
			else if (spaces[i] == PLAYER_X)
				ss << "X";
			else
				ss << "-";
		}
		ss << std::endl;
	}

	return ss.str();
}

std::string TTTMove::toString() {
	std::stringstream ss;
	ss << "(" << ((int) index) << ", " << (p == PLAYER_O ? "O" : "X") << ")";
	return ss.str();
}