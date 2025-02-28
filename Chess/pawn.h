#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn : public Piece
{
public:

	void move() const override;

protected:

	Pawn(char symbol, Color color, Type type)
		: Piece{ symbol, color, type }
	{
	}

	friend class PieceFactory;
};

#endif