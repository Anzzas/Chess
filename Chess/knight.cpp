#include "knight.h"

bool Knight::canMoveTo(const BoardState& board, const Position startPosition, const Position targetPosition) const
{
	// Starting case coordinates
	const auto y_Start{ startPosition.getY() };
	const auto x_Start{ startPosition.getX() };

	// Target case coordinates 
	const auto y_Target{ targetPosition.getY() };
	const auto x_Target{ targetPosition.getX() };

	if ((y_Target == y_Start - 2 || y_Target == y_Start + 2) && (x_Target == x_Start + 1 || x_Target == x_Start - 1))
		return true;

	else if ((y_Target == y_Start + 1 || y_Target == y_Start - 1) && (x_Target == x_Start + 2 || x_Target == x_Start - 2))
		return true;

	return false;
}