#include "queen.h"
#include "board.h"

bool Queen::canMoveTo(const Board& board, const std::pair<size_t, size_t> startPosition, const std::pair<size_t, size_t> targetPosition) const
{
	// Starting case coordinates
	const auto [y_Start, x_Start] = startPosition;

	// Target case coordinates 
	const auto [y_Target, x_Target] = targetPosition;

	// Verifying diagonal movement
	size_t deltaX = (x_Start > x_Target) ? (x_Start - x_Target) : (x_Target - x_Start);
	size_t deltaY = (y_Start > y_Target) ? (y_Start - y_Target) : (y_Target - y_Start);

	if (deltaX == deltaY) // If it's a diagonal movement
	{
		if (x_Start != x_Target && y_Start != y_Target)
		{
			// Moving down right
			if (y_Start < y_Target && x_Start < x_Target)
			{
				size_t y{ y_Start + 1 };
				size_t x{ x_Start + 1 };

				while (y < y_Target && x < x_Target)
				{

					if (!board.getBoard()[y][x].isEmpty())
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
					if (!board.getBoard()[y][x].isEmpty())
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
					if (!board.getBoard()[y][x].isEmpty())
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
					if (!board.getBoard()[y][x].isEmpty())
						return false;
					y--;
					x--;
				}
			}
		}
		return true;
	}

	// Vertical and horizontal movements check
	// Y axis (vertical)
	else if (y_Target != y_Start && x_Target == x_Start)
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

	// X axis (horizontal)
	else if (x_Target != x_Start && y_Target == y_Start)
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