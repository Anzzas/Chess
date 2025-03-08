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
			// Moving 2 cases at starting case
			if (y_Start == 6 && (y_Target == y_Start - 1 || y_Target == y_Start - 2) && x_Target == x_Start && TargetCase.isEmpty())
				return true;

			// Moving 1 case
			else if (y_Target == y_Start - 1 && x_Target == x_Start)
				return true;

			else
				return false;
		}

		else // If it's a BLACK piece
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