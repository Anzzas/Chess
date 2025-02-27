#include "queen.h"

Queen Queen::createQueen(Color color)
{
	return Queen{ 'Q', color, Type::queen };
}

void Queen::move() const
{
	std::cout << "moving diagonally or in line\n";
}