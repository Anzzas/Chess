#include "king.h"

King King::createPawn(Color color)
{
	return King{ 'K', color, Type::king };
}

void King::move() const
{
	std::cout << "moving diagonally or in line by 1 case\n";
}