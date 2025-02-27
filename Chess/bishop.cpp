#include "bishop.h"

Bishop Bishop::createPawn(Color color)
{
	return Bishop{ 'B', color, Type::bishop };
}

void Bishop::move() const
{
	std::cout << "moving diagonally\n";
}