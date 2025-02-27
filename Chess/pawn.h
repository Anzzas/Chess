#ifndef PAWN_H
#define PAWN_H
#include "piece.h"


class Pawn : public Piece
{
public:

	static Pawn createPawn(Color color);
	void move() const override;

private:

	Pawn(char symbol, Color color, Type type)
		: Piece{ symbol, color, type }
	{
	}
};

#endif