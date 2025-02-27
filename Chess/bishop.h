#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

class Bishop : public Piece
{
public:

	static Bishop createPawn(Color color);
	void move() const override;

private:

	Bishop(char symbol, Color color, Type type)
		: Piece{ symbol, color, type }
	{
	}
};

#endif