#include "knight.h"

Knight Knight::createKnight(Color color)
{
	return Knight{ 'N', color, Type::knight };
}

void Knight::move() const
{
	std::cout << "moving like an L\n";
}