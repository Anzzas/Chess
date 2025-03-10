#include "pawn.h"
#include "board.h"

bool Pawn::canMoveTo(const Board& board, const std::pair<size_t, size_t> startPosition, const std::pair<size_t, size_t> targetPosition) const
{

	const auto [y_Start, x_Start] = startPosition;
	const auto [y_Target, x_Target] = targetPosition;
	const Case& TargetCase{ board.getBoard()[y_Target][x_Target] };

	if (TargetCase.isEmpty())
	{
		if (m_color == Piece::white)
		{
			// Moving 2 cases at starting Pawn case (for white Y = 6)
			if (y_Start == 6 && y_Target == y_Start - 2 && x_Target == x_Start)
			{
				setHasMovedTwoSquares(true);
				return true;
			}

			// Moving 1 case
			else if (y_Target == y_Start - 1 && x_Target == x_Start)
				return true;

			else
				return false;
		}

		else // If it's a BLACK piece
		{
			// Moving 2 cases at starting case OR moving by 1 case
			if (y_Start == 1 && (y_Target == y_Start + 1 || y_Target == y_Start + 2) && x_Target == x_Start && TargetCase.isEmpty())
				return true;

			if (y_Target == y_Start + 1 && x_Target == x_Start)
				return true;

			else
				return false;
		}
	}

	// If TargetCase is NOT empty, verifying if can take in diagonal
	if (m_color == Piece::white)
	{
		if (y_Target == y_Start - 1 && (x_Target == x_Start + 1 || x_Target == x_Start - 1))
			return true;
	}
	else // If it's a BLACK piece
	{
		if (y_Target == y_Start + 1 && (x_Target == x_Start + 1 || x_Target == x_Start - 1))
			return true;
	}

	return false;
}

void Pawn::resetAllPawnFlags(const Board& b, Piece::Color color)
{
	const auto& board{ b.getBoard() };

	for (size_t y = 0; y < boardSettings::boardSize; y++)
	{
		for (size_t x = 0; x < boardSettings::boardSize; x++)
		{
			if (board[y][x].getPiece().getType() == Piece::pawn && board[y][x].getPiece().getColor() == color)
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

void Pawn::setHasMovedTwoSquares(bool state)
{
	m_hasMovedTwoSquares = state;
}