#include "king.h"
#include "board.h"

void King::move() const
{
	std::cout << "moving diagonally or in line by 1 case\n";
}

bool King::canMoveTo(const Board& board, std::pair<size_t, size_t> startPosition, std::pair<size_t, size_t> targetPosition) const
{
	// Starting case coordinates
	const size_t x_Start{ startPosition.second };
	const size_t y_Start{ startPosition.first };

	// Target case coordinates 
	const Case& TargetCase{ board.getBoard()[targetPosition.first][targetPosition.second] };
	const size_t x_Target{ targetPosition.second };
	const size_t y_Target{ targetPosition.first };

	// Check up, down, right, left directions
	if (y_Target == y_Start + 1 || y_Target == y_Start - 1 || x_Target == x_Start + 1 || x_Target == x_Start - 1)
		return true;

	// Check down-right, down-left directions
	if ((y_Target == y_Start + 1 && x_Target == x_Start - 1) || (y_Target == y_Start + 1 && x_Target == x_Start + 1))
		return true;

	// Check up-right, up-left directions
	if ((y_Target == y_Start - 1 && x_Target == x_Start - 1) || (y_Target == y_Start - 1 && x_Target == x_Start + 1))
		return true;

	return false;
}