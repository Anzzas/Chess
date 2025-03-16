#include "moveValidator.h"

using enum Color;
using enum Type;
using enum MoveType;

bool MoveValidator::isValidMove(const BoardState& board, const Move& move, Color playerColor) const
{
	switch (move.getMoveType())
	{
	case MoveType::normal: return validateNormalMove(board, move, playerColor);
	case MoveType::castling: return validateCastlingMove(board, move, playerColor);
	case MoveType::promotion: return validatePromotionMove(board, move, playerColor);
	case MoveType::enPassant: return validateEnPassantMove(board, move, playerColor);
	}

	return false;
}

MoveType MoveValidator::determineMoveType(const BoardState& board, const Move& move, Color playerColor) const
{
	if (isPromotionMove(board, move, playerColor))
		return promotion;

	else if (isEnPassantMove(board, move, playerColor))
		return enPassant;

	return normal;
}

bool MoveValidator::isPromotionMove(const BoardState& board, const Move& move, Color playerColor) const
{
	size_t PromotionY{ playerColor == white ? 0 : 7 };
	Type fromPieceType{ board.getPieceTypeAt(move.getFrom()) };

	if (fromPieceType == pawn && move.getTo().getY() == PromotionY)
		return true;

	return false;
}

bool MoveValidator::isEnPassantMove(const BoardState& board, const Move& move, Color playerColor) const
{
	if (board.getPieceTypeAt(move.getFrom()) != pawn)
		return false;

	if (dynamic_cast<const Pawn*>(board.getPieceAt(move.getFrom()))->isEnPassant(board, move.getFrom(), move.getTo()))
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

bool MoveValidator::validateNormalMove(const BoardState& board, const Move& move, Color playerColor) const
{
	const Piece* fromPiece{ board.getPieceAt(move.getFrom()) };

	return fromPiece->canMoveTo(board, move.getFrom(), move.getTo());
}

bool MoveValidator::validateCastlingMove(const BoardState& board, const Move& move, Color playerColor) const
{	 
	const size_t y(playerColor == white ? 7 : 0);
	const Position& rookPosition{ move.getFrom() };
	const Position& kingPosition{ move.getTo() };

	const auto* const king{ dynamic_cast<const King*>(board.getPieceAt(kingPosition)) };
	const auto* const rook{ dynamic_cast<const Rook*>(board.getPieceAt(rookPosition)) };

	if (!king || king->getHasMoved() || !rook || rook->getHasMoved())
		return false;

	std::vector<Position> inBetweenSquares{ board.getSquaresBetween(kingPosition, rookPosition) };

	for (const auto& square : inBetweenSquares)
	{
		if (!board.isEmpty(square) || board.isPositionUnderAttack(square, playerColor == white ? black : white))
			return false;
	}

	return true;
}	 
	 
bool MoveValidator::validateEnPassantMove(const BoardState& board, const Move& move, Color playerColor) const
{	 
	if (move.getFromType() != pawn)
		return false;

	const Pawn* pawn{ dynamic_cast<const Pawn*>(board.getPieceAt(move.getFrom())) };
	
	if(pawn->isEnPassant(board, move.getFrom(), move.getTo()))
		return true;

	return false;
}	 
	 
bool MoveValidator::validatePromotionMove(const BoardState& board, const Move& move, Color playerColor) const
{
	size_t promotionY{ playerColor == white ? 0 : 7 };

	if (move.getFromType() == pawn && move.getTo().getY() == promotionY)
		return true;

	return false;
}