#include "bishop.h"
#include "board.h"

void Bishop::move() const
{
	std::cout << "moving diagonally\n";
}

bool Bishop::canMoveTo(const Board& board, std::pair<size_t, size_t> startPosition, std::pair<size_t, size_t> targetPosition) const
{
	// Starting case coordinates
	const size_t x_Start{ startPosition.second };
	const size_t y_Start{ startPosition.first };

	// Target case coordinates 
	const Case& TargetCase{ board.getBoard()[targetPosition.first][targetPosition.second] };
	const size_t x_Target{ targetPosition.second };
	const size_t y_Target{ targetPosition.first };


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
		return true;
	}
	return false;
}