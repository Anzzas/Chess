#include "pawn.h"
#include "board.h"

bool Pawn::canMoveTo(const Board& board, const std::pair<size_t, size_t> startPosition, const std::pair<size_t, size_t> targetPosition) const
{

	const auto [y_Start, x_Start] = startPosition;
	const auto [y_Target, x_Target] = targetPosition;
	const Case& TargetCase{ board.getBoard()[y_Target][x_Target] };

	const int forwardDirection = (m_color == Piece::white) ? -1 : 1;
	const int startingRank = (m_color == Piece::white) ? 6 : 1;

	if (TargetCase.isEmpty())
	{
		for (auto offsetX : {-1, 1})
		{
			// EN-PASSANT CHECK
			// Checking if there's a piece at the RIGHT and if this piece is a Pawn of the opposite color
			if (x_Start + offsetX >= 0 && x_Start + offsetX < boardSettings::boardSize)
			{
				const auto& adjacentCase{ board.getBoard()[y_Start][x_Start + offsetX] };

				if (!adjacentCase.isEmpty() && adjacentCase.getPiece().getType() == Piece::pawn && adjacentCase.getPiece().getColor() != m_color)
				{
					// Then checking if this Pawn has moved two squares forward to check if we can take by "en-passant"
					if (dynamic_cast<Pawn*>(adjacentCase.getCase().get())->hasMovedTwoSquares() && (y_Target == y_Start + forwardDirection && x_Target == x_Start + offsetX))
					{
						m_hasUsedEnPassant = true;
						return true;
					}
				}
			}
		}

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

void Pawn::resetAllPawnFlags(const Board& b, Piece::Color color)
{
	const auto& board{ b.getBoard() };

	for (size_t y = 0; y < boardSettings::boardSize; y++)
	{
		for (size_t x = 0; x < boardSettings::boardSize; x++)
		{
			if (!board[y][x].isEmpty() && board[y][x].getPiece().getType() == Piece::pawn && board[y][x].getPiece().getColor() == color)
			{
				dynamic_cast<Pawn*>(board[y][x].getCase().get())->m_hasMovedTwoSquares = false;
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