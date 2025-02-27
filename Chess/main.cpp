#include <iostream>
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "case.h"

int main()
{
	Case c{};

	c.setPiece(Pawn::createPawn(Piece::black));


	std::cout << c << "\n";
}