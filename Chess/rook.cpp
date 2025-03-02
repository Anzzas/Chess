#include "rook.h"
#include "board.h"

void Rook::move() const
{

}

bool Rook::canMoveTo(const Board& board, std::pair<size_t, size_t> startPosition, std::pair<size_t, size_t> targetPosition) const
{
	// Starting case coordinates
	const size_t x_Start{ startPosition.second };
	const size_t y_Start{ startPosition.first };

	// Target case coordinates 
	const Case& TargetCase{ board.getBoard()[targetPosition.first][targetPosition.second] };
	const size_t x_Target{ targetPosition.second };
	const size_t y_Target{ targetPosition.first };


	// Y axis
	if (y_Target != y_Start && x_Target == x_Start)
	{
		// Moving up
		for (size_t y{ y_Start }; y > y_Target; y--)
		{
			if (!board.getBoard()[y - 1][x_Start].isEmpty() && y - 1 != y_Target)
				return false;
		}

		// Moving down
		for (size_t y{ y_Start }; y < y_Target; y++)
		{
			if (!board.getBoard()[y + 1][x_Start].isEmpty() && y + 1 != y_Target)
				return false;
		}
		return true;
	}

	// X axis
	if (x_Target != x_Start && y_Target == y_Start)
	{
		// Moving to the right
		for (size_t x{ x_Start }; x < x_Target; x++)
		{
			if (!board.getBoard()[y_Start][x + 1].isEmpty() && x + 1 != x_Target)
				return false;
		}

		// Moving to the left
		for (size_t x{ x_Start }; x > x_Target; x--)
		{
			if (!board.getBoard()[y_Start][x - 1].isEmpty() && x - 1 != x_Target)
				return false;
		}
		return true;
	}
	return false;
}