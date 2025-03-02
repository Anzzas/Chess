#include "knight.h"

void Knight::move() const
{
	std::cout << "moving like an L\n";
}

bool Knight::canMoveTo(const Board& board, std::pair<size_t, size_t> startPosition, std::pair<size_t, size_t> targetPosition) const
{
	return true;
}