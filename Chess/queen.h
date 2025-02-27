#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

class Queen : public Piece
{
public:

	static Queen createPawn(Color color);
	void move() const override;

private:

	Queen(char symbol, Color color, Type type)
		: Piece{ symbol, color, type }
	{
	}
};

#endif