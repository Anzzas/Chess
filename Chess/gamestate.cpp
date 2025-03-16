#include "gamestate.h"

using enum Color;

bool GameState::makeMove(Move move)
{

	const Piece* fromPiece{ m_board.getPieceAt(move.getFrom()) };
	const Piece* toPiece{ m_board.getPieceAt(move.getTo()) };

	if (move.getMoveType() != MoveType::castling)
	{
		MoveType newMoveType{ m_validator.determineMoveType(m_board, move, m_currentPlayer) };
		move.setMoveType(newMoveType);
	}

	// Verifying if Move is valid
	if (!m_validator.isValidMove(m_board, move, m_currentPlayer))
		return false;

	// Executing Move
	m_executor.executeMove();

	// Adding Move to Move History
	m_history.addMove(move);

	// Verifying GameRule (Check, CheckMate, StaleMate)
	if (m_rules.isCheckmate() || m_rules.isStalemate())
		// end game

	else if (m_rules.isKingInCheck())
		// check

	setNextPlayer();

	return true;
}

void GameState::setNextPlayer() { m_currentPlayer = m_currentPlayer == white ? black : white; }