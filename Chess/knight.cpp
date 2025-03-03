#include "knight.h"
#include "board.h"

void Knight::move() const
{

}

bool Knight::canMoveTo(const Board& board, std::pair<size_t, size_t> startPosition, std::pair<size_t, size_t> targetPosition) const
{
	// Starting case coordinates
	const size_t x_Start{ startPosition.second };
	const size_t y_Start{ startPosition.first };

	// Target case coordinates 
	const size_t x_Target{ targetPosition.second };
	const size_t y_Target{ targetPosition.first };

	if ((y_Target == y_Start - 2 || y_Target == y_Start + 2) && (x_Target == x_Start + 1 || x_Target == x_Start - 1))
		return true;

	else if ((y_Target == y_Start + 1 || y_Target == y_Start - 1) && (x_Target == x_Start + 2 || x_Target == x_Start - 2))
		return true;

	return false;
}