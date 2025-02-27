#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook : public Piece
{
public:

	static Rook createPawn(Color color);
	void move() const override;

private:

	Rook(char symbol, Color color, Type type)
		: Piece{ symbol, color, type }
	{
	}
};

#endif