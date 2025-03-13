#include "gamestate.h"

bool GameState::makeMove(Position from, Position to)
{

	const Piece* fromPiece{ m_board.getPieceAt(from) };
	const Piece* toPiece{ m_board.getPieceAt(to) };
	Type toType{toPiece ? toPiece->getType() : max_types};


	Move move{ fromPiece->getType(), toType, from, to };


	if (m_validator.isValidMove(m_board, move))
	{

	}
}