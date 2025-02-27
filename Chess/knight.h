#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

class Knight : public Piece
{
public:

	static Knight createPawn(Color color);
	void move() const override;

private:

	Knight(char symbol, Color color, Type type)
		: Piece{ symbol, color, type }
	{
	}
};

#endif