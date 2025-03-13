#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "moveExecutor.h"
#include "gameRules.h"
#include "moveHistory.h"

class Position;

class GameState
{
public:

	bool makeMove(Position from, Position to);
	bool isGameOver() const;

private:

	Board board;
	Color currentPlayer;
	MoveHistory history;
	GameStatus status;
};

#endif