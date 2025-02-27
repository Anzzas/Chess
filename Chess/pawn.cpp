#include "pawn.h"

Pawn Pawn::createPawn(Color color)
{
	return Pawn{ 'P', color, Type::pawn };
}

void Pawn::move() const
{

}