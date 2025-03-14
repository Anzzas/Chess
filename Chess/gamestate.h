#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "moveExecutor.h"
#include "gameRules.h"
#include "moveHistory.h"
#include "move.h"

class Position;

class GameState
{
public:

	GameState()
		: m_currentPlayer{ white }
	{
	}

	bool makeMove(Position from, Position to);
	bool isGameOver() const;

private:

	Board m_board{};
	Color m_currentPlayer{};
	MoveHistory m_history{};
	GameRules m_rules{};
	MoveExecutor m_executor{};
	MoveValidator m_validator{};

};

#endif