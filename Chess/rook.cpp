#include "rook.h"

bool Rook::canMoveTo(const BoardState& board, const Position startPosition, const Position targetPosition) const
{
	// Starting case coordinates
	const auto y_Start{ startPosition.getY() };
	const auto x_Start{ startPosition.getX() };

	// Target case coordinates 
	const auto y_Target{ targetPosition.getY() };
	const auto x_Target{ targetPosition.getX() };

	// Y axis
	if (y_Target != y_Start && x_Target == x_Start)
	{
		// Moving up
		for (size_t y{ y_Start }; y > y_Target; y--)
		{
			if (!board.isEmpty({y - 1, x_Start}) && y - 1 != y_Target)
				return false;
		}

		// Moving down
		for (size_t y{ y_Start }; y < y_Target; y++)
		{
			if (!board.isEmpty({y + 1, x_Start}) && y + 1 != y_Target)
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
			if (!board.isEmpty({y_Start, x + 1}) && x + 1 != x_Target)
				return false;
		}

		// Moving to the left
		for (size_t x{ x_Start }; x > x_Target; x--)
		{
			if (!board.isEmpty({y_Start, x - 1}) && x - 1 != x_Target)
				return false;
		}
		return true;
	}
	return false;
}

const bool& Rook::getHasMoved() const { return hasMoved; }

void Rook::setHasMoved(bool hasMoved) { this->hasMoved = hasMoved; }