# TicTacToe-AI
Using minimax to solve the difficult game of tic tac toe!
This is my first experiment with minimax. I will be working my way up to solving progressively harder games with more advanced optimizations and techniques.

# Algorithm
https://en.wikipedia.org/wiki/Minimax

# Usage
build
```
make
```
run
```
./program
```

# Sample Output
```txt
loading tic tac toe engine by Gareth George

Players: X (human), O (human), - (bot)
	select your player (X or O or -): -
PLAYER 1's (BOT) MOVE
---
---
---
bot running minimax...
	generated move: (0, X) (score: 0)
PLAYER 2's (BOT) MOVE
X--
---
---
bot running minimax...
	generated move: (2, O) (score: 0)
PLAYER 1's (BOT) MOVE
X-O
---
---
bot running minimax...
	generated move: (6, X) (score: 0)
PLAYER 2's (BOT) MOVE
X-O
---
X--
bot running minimax...
	generated move: (3, O) (score: 0)
PLAYER 1's (BOT) MOVE
X-O
O--
X--
bot running minimax...
	generated move: (1, X) (score: 0)
PLAYER 2's (BOT) MOVE
XXO
O--
X--
bot running minimax...
	generated move: (4, O) (score: 0)
PLAYER 1's (BOT) MOVE
XXO
OO-
X--
bot running minimax...
	generated move: (5, X) (score: 0)
PLAYER 2's (BOT) MOVE
XXO
OOX
X--
bot running minimax...
	generated move: (7, O) (score: 0)
PLAYER 1's (BOT) MOVE
XXO
OOX
XO-
bot running minimax...
	generated move: (8, X) (score: 0)
GAME OVER!!!!
XXO
OOX
XOX
```
