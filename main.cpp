#include <iostream>
#include "board.h"

class Player {
protected:
	piece myPiece;
public:
	Player(piece myPiece) : myPiece(myPiece) {

	}

	piece getOtherPlayerPiece() {
		return myPiece == PLAYER_O ? PLAYER_X : PLAYER_O;
	}

	virtual TTTMove move(TTTBoard& board) = 0;
	virtual const char* getType() = 0;
};

class PlayerHuman : public Player {
public:
	PlayerHuman(piece myPiece) : Player(myPiece) { }

	TTTMove move(TTTBoard& board) {
		std::string coordinates;

		int x;
		int y;

		while (true) {
			std::cout << "enter coordinates (x [1-3], y [1-3]): " << std::flush;
			try {
				std::string xstr;
				std::string ystr;
				std::getline(std::cin, xstr, ',');
				std::getline(std::cin, ystr);
				x = std::stoi(xstr);
				y = std::stoi(ystr);
			} catch (const std::invalid_argument& ia) {
				std::cout << "invalid argument  \'" << ia.what() << "\'." << std::endl;
				continue ;
			}
			if (x < 1 || x > 3 || y < 1 || y > 3) {
				std::cout << "arguments (" << x << ", " << y << ") must both be in the range 1 <= x <= 3 && 1 <= y <= 3" << std::endl;
			}

			break ;
		}

		// player's preferred move
		int index = (y - 1) * 3 + (x - 1);
		TTTMove moveSelected(index, myPiece);

		// algorithm's best move
		TTTMove bestMove;
		int score = board.minimax(myPiece, myPiece, bestMove);
		
		// info printout!		
		std::cout << "\tplayer selected move: " << moveSelected.toString() << std::endl;
		std::cout << "\tmove program would have made: " << bestMove.toString() << " (score: " << score << ")" << std::endl;

		return moveSelected;
	}

	const char* getType() {
		return "HUMAN";
	}
};

class PlayerBot : public Player {
public:
	PlayerBot(piece myPiece) : Player(myPiece) { }

	TTTMove move(TTTBoard& board) {
		std::cout << "bot running minimax..." << std::endl;
		TTTMove bestMove;
		int score = board.minimax(myPiece, myPiece, bestMove);
		std::cout << "\tgenerated move: " << bestMove.toString() << " (score: " << score << ")" << std::endl;

		return bestMove;
	}

	const char* getType() {
		return "BOT";
	}
};

int main() {
	std::cout << "loading tic tac toe engine by Gareth George\n" << std::endl;

	Player* player1 = nullptr;
	Player* player2 = nullptr;

	{	
		std::cout << "Players: X (human), O (human), - (bot)" << std::endl;
		std::cout << "\tselect your player (X or O or -): " << std::flush;
		char playerLetter;
		std::cin >> playerLetter;


		if (playerLetter == 'X') {
			player1 = dynamic_cast<Player*>(new PlayerHuman(PLAYER_X));
			player2 = dynamic_cast<Player*>(new PlayerBot(PLAYER_O));
		} else if (playerLetter == 'O') {
			player1 = dynamic_cast<Player*>(new PlayerBot(PLAYER_X));
			player2 = dynamic_cast<Player*>(new PlayerHuman(PLAYER_O));
		} else {
			player1 = dynamic_cast<Player*>(new PlayerBot(PLAYER_X));
			player2 = dynamic_cast<Player*>(new PlayerBot(PLAYER_O));
		}
	}

	TTTBoard board;

	while (true) {

		// p1
		if (board.isGameOver())
			break ;

		std::cout << "PLAYER 1's (" << player1->getType() << ") MOVE" << std::endl;
		std::cout << board.toString();
		TTTMove p1move = player1->move(board);
		p1move.apply(board);

		// p2
		if (board.isGameOver())
			break ;

		std::cout << "PLAYER 2's (" << player2->getType() << ") MOVE" << std::endl;
		std::cout << board.toString();
		TTTMove p2move = player2->move(board);
		p2move.apply(board);
	}

	std::cout << "GAME OVER!!!!" << std::endl;
	std::cout << board.toString();
}