#include "bishop.h"

bool Bishop::canMoveTo(const BoardState& board, const Position startPosition, const Position targetPosition) const
{
	// Starting case coordinates
	const auto y_Start{ startPosition.getY() };
	const auto x_Start{ startPosition.getX() };


	// Target case coordinates 
	const auto y_Target{ targetPosition.getY() };
	const auto x_Target{ targetPosition.getX() };


	// Verifying diagonal movement
	size_t deltaX = (x_Start > x_Target) ? (x_Start - x_Target) : (x_Target - x_Start);
	size_t deltaY = (y_Start > y_Target) ? (y_Start - y_Target) : (y_Target - y_Start);

	if (deltaX != deltaY) 
		return false; // Not a diagonal movement

	if (x_Start != x_Target && y_Start != y_Target)
	{
		// Moving down right
		if (y_Start < y_Target && x_Start < x_Target)
		{
			size_t y{ y_Start + 1 };
			size_t x{ x_Start + 1 };

			while (y < y_Target && x < x_Target)
			{

				if (!board.isEmpty({y, x}))
					return false;
				y++;
				x++;
			}
		}

		// Moving down left
		else if (y_Start < y_Target && x_Start > x_Target)
		{
			size_t y{ y_Start + 1 };
			size_t x{ x_Start - 1 };

			while (y < y_Target && x > x_Target)
			{
				if (!board.isEmpty({ y, x }))
					return false;
				y++;
				x--;
			}
		}

		// Moving up right
		else if (y_Start > y_Target && x_Start < x_Target)
		{
			size_t y{ y_Start - 1 };
			size_t x{ x_Start + 1 };

			while (y > y_Target && x < x_Target)
			{
				if (!board.isEmpty({ y, x }))
					return false;
				y--;
				x++;
			}
		}

		// Moving up left
		else if (y_Start > y_Target && x_Start > x_Target)
		{
			size_t y{ y_Start - 1 };
			size_t x{ x_Start - 1 };

			while (y > y_Target && x > x_Target)
			{
				if (!board.isEmpty({ y, x }))
					return false;
				y--;
				x--;
			}
		}
		return true;
	}
	return false;
}