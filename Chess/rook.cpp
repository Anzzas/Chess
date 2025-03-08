#include "rook.h"
#include "board.h"

bool Rook::canMoveTo(const Board& board, const std::pair<size_t, size_t> startPosition, const std::pair<size_t, size_t> targetPosition) const
{
	// Starting case coordinates
	const auto [y_Start, x_Start] = startPosition;

	// Target case coordinates 
	const auto [y_Target, x_Target] = targetPosition;

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

const bool& Rook::getHasMoved() const { return hasMoved; }

void Rook::setHasMoved(bool hasMoved) { this->hasMoved = hasMoved; }