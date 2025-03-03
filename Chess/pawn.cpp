#include "pawn.h"
#include "board.h"

void Pawn::move() const
{
	
}

bool Pawn::canMoveTo(const Board& board, const std::pair<size_t, size_t> startPosition, const std::pair<size_t, size_t> targetPosition) const
{
	const size_t x_Start{ startPosition.second };
	const size_t y_Start{ startPosition.first };

	const Case& TargetCase{ board.getBoard()[targetPosition.first][targetPosition.second] };
	const size_t x_Target{ targetPosition.second };
	const size_t y_Target{ targetPosition.first };

	if (TargetCase.isEmpty())
	{
		if (m_color == Piece::white)
		{
			// Moving 2 cases at starting case
			if (y_Start == 6 && (y_Target == y_Start - 1 || y_Target == y_Start - 2) && x_Target == x_Start && TargetCase.isEmpty())
				return true;

			// Moving 1 case
			else if (y_Target == y_Start - 1 && x_Target == x_Start)
				return true;

			else
				return false;
		}

		else if (m_color == Piece::black)
		{
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