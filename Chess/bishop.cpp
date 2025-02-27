#include "bishop.h"

Bishop Bishop::createBishop(Color color)
{
	return Bishop{ 'B', color, Type::bishop };
}

void Bishop::move() const
{
	std::cout << "moving diagonally\n";
}