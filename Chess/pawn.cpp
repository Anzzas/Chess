#include "pawn.h"

using enum Type;
using enum Color;

bool Pawn::canMoveTo(const BoardState& board, const Position startPosition, const Position targetPosition) const
{

	const auto y_Start{ startPosition.getY() };
	const auto x_Start{ startPosition.getX() };

	const auto y_Target{ targetPosition.getY() };
	const auto x_Target{ targetPosition.getX() };

	const int forwardDirection = (m_color == white) ? -1 : 1;
	const int startingRank = (m_color == white) ? 6 : 1;

	if (board.isEmpty(targetPosition))
	{
		if (isEnPassant(board, startPosition, targetPosition))
			return true;

		// Moving 2 cases FORWARD at starting Pawn case
		if (y_Start == startingRank && y_Target == y_Start + (forwardDirection * 2) && x_Target == x_Start)
		{
			setHasMovedTwoSquares(true);
			return true;
		}

		// Moving by 1 case
		else if (y_Target == y_Start + forwardDirection && x_Target == x_Start)
			return true;

		return false;
	}

	// If TargetCase is NOT empty, verifying if can take in diagonal
	if (y_Target == y_Start + forwardDirection && (x_Target == x_Start + 1 || x_Target == x_Start - 1))
		return true;

	return false;
}

void Pawn::resetAllPawnFlags(const BoardState& b, Color color)
{
	//const auto& board{ b.getBoard() };

	for (size_t y = 0; y < boardSettings::boardSize; y++)
	{
		for (size_t x = 0; x < boardSettings::boardSize; x++)
		{
			if (!b.isEmpty({y, x}) && b.getPieceAt({y, x})->getType() == pawn && b.getPieceAt({y, x})->getColor() == color)
			{
				dynamic_cast<Pawn*>(b.getPieceAt({y, x}))->m_hasMovedTwoSquares = false;
			}
		}
	}
}

const bool& Pawn::hasMovedTwoSquares() const
{
	return m_hasMovedTwoSquares;
}

void Pawn::setHasMovedTwoSquares(bool state) const
{
	m_hasMovedTwoSquares = state;
}

const bool& Pawn::hasUsedEnPassant() const
{
	return m_hasUsedEnPassant;
}

void Pawn::setHasUsedEnPassant(bool state) const
{
	m_hasUsedEnPassant = state;
}

bool Pawn::isEnPassant(const BoardState& board, const Position& from, const Position& to) const
{
	const int forwardDirection = (m_color == white) ? -1 : 1;

	for (auto offsetX : { -1, 1 })
	{
		// EN-PASSANT CHECK
		// Checking if there's a piece at the RIGHT or LEFT and if this piece is a Pawn of the opposite color
		if (from.getX() + offsetX >= 0 && from.getX() + offsetX < boardSettings::boardSize)
		{
			const Piece* adjacentPiece{ board.getPieceAt({from.getY(), from.getX() + offsetX})};

			bool isPawnOfOppositeColor{ adjacentPiece && adjacentPiece->getType() == pawn && adjacentPiece->getColor() != m_color };
			bool hasMovedTwoSquares{ dynamic_cast<const Pawn*>(adjacentPiece)->hasMovedTwoSquares() };
			bool isTargetSquareBehindEnemyPawn{ to.getY() == from.getY() + forwardDirection && to.getX() == from.getX() + offsetX };

			if (isPawnOfOppositeColor && hasMovedTwoSquares && isTargetSquareBehindEnemyPawn)
				return true;
		}
	}
	return false;
}