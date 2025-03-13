#include "moveValidator.h"

bool MoveValidator::isValidMove(const BoardState& board, const Move& move) const
{
	if (move.getFrom().isValid() && move.getTo().isValid())
		return true;

	return false;
}

bool MoveValidator::wouldLeaveKingInCheck(const BoardState& board, Position from, Position to, Color playerColor) const
{
	const auto fromY{ from.getY() };
	const auto fromX{ from.getX() };

	const auto toY{ to.getY() };
	const auto toX{ to.getX() };

	// Simulating move to verify is the player don't put himself in check
	// Getting a copy of the starting case before moving them and later verifying if targetCase was not empty to get also a copy
	auto tempStartPiece{ PieceFactory::createPiece(board.getPieceAt(from)->getType(), board.getPieceAt(from)->getColor())};

	// Special case for Pawn (copying a specific variable)
	if (tempStartPiece->getType() == pawn)
	{
		dynamic_cast<Pawn*>(tempStartPiece.get())->setHasMovedTwoSquares(dynamic_cast<Pawn*>(board.getPieceAt(from))->hasMovedTwoSquares());
		dynamic_cast<Pawn*>(tempStartPiece.get())->setHasUsedEnPassant(dynamic_cast<Pawn*>(board.getPieceAt(from))->hasUsedEnPassant());
	}

	std::unique_ptr<Piece> tempTargetPiece{};

	// If the targetCase is not empty then create a copy of it to restore it later
	if (!board.isEmpty(to))
		tempTargetPiece = PieceFactory::createPiece(board.getPieceAt(to)->getType(), board.getPieceAt(to)->getColor());

	
	movePiece(from, to); // Move the piece normally

	if (!board.isKingInCheck(playerTurn)) // If player own king is not self checked after the move, then everything is OK
	{
		// Putting back the pieces to their original cases
		m_board[fromY][fromX].getCase() = std::move(tempStartPiece);
		m_board[toY][toX].getCase() = std::move(tempTargetPiece);
		return false;
	}

	// Else, the king after the move is in fact in check
	// Putting back the moved piece to their original cases
	m_board[startCaseY][startCaseX].getCase() = std::move(tempStartCase);
	m_board[targetCaseY][targetCaseX].getCase() = std::move(tempTargetCase);

	return true; // If that move put the player himself in check, make the player try again
}