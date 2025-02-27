#include "queen.h"

Queen Queen::createPawn(Color color)
{
	return Queen{ 'Q', color, Type::queen };
}

void Queen::move() const
{
	std::cout << "moving diagonally or in line\n";
}