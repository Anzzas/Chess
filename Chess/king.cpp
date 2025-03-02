#include "king.h"

void King::move() const
{
	std::cout << "moving diagonally or in line by 1 case\n";
}

bool King::canMoveTo(const Board& board, std::pair<size_t, size_t> startPosition, std::pair<size_t, size_t> targetPosition) const
{
	return true;
}