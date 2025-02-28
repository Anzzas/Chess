#ifndef KING_H
#define KING_H
#include "piece.h"

class King : public Piece
{
public:

	void move() const override;

private:

	King(char symbol, Color color, Type type)
		: Piece{ symbol, color, type }
	{
	}

	friend class PieceFactory;
};

#endif