#include <iostream>
#include "pawn.h"

int main()
{
	Pawn pawn{Pawn::createPawn(Piece::black)};
	Piece* pawn2{ new Pawn {Pawn::createPawn(Piece::black)} };
}