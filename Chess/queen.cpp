#include "queen.h"

void Queen::move() const
{
	std::cout << "moving diagonally or in line\n";
}

bool Queen::canMoveTo(const Board& board, std::pair<size_t, size_t> startPosition, std::pair<size_t, size_t> targetPosition) const
{
	return true;
}