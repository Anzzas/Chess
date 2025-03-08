#include "knight.h"
#include "board.h"

bool Knight::canMoveTo(const Board& board, const std::pair<size_t, size_t> startPosition, const std::pair<size_t, size_t> targetPosition) const
{
	// Starting case coordinates
	const auto [y_Start, x_Start] = startPosition;

	// Target case coordinates 
	const auto [y_Target, x_Target] = targetPosition;

	if ((y_Target == y_Start - 2 || y_Target == y_Start + 2) && (x_Target == x_Start + 1 || x_Target == x_Start - 1))
		return true;

	else if ((y_Target == y_Start + 1 || y_Target == y_Start - 1) && (x_Target == x_Start + 2 || x_Target == x_Start - 2))
		return true;

	return false;
}