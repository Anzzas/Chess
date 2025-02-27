#include "knight.h"

Knight Knight::createPawn(Color color)
{
	return Knight{ 'N', color, Type::knight };
}

void Knight::move() const
{
	std::cout << "moving like an L\n";
}