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
		: m_currentPlayer{ Color::white }
	{
	}

	bool makeMove(Move move);
	bool isGameOver() const;
	void setNextPlayer();

	const Board& getBoard() const { return m_board; }
	const Color& getCurrentPlayer() const { return m_currentPlayer; }

private:

	Board m_board{};
	Color m_currentPlayer{};
	MoveValidator m_validator{};
	MoveExecutor m_executor{};
	MoveHistory m_history{};
	GameRules m_rules{};
};

#endif