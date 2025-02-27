#include "rook.h"

Rook Rook::createRook(Color color)
{
	return Rook{ 'R', color, Type::rook };
}

void Rook::move() const
{
	std::cout << "moving like an L\n";
}