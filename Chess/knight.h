#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

class Knight : public Piece
{
public:

	bool canMoveTo(const BoardState& board, const Position startPosition, const Position targetPosition) const override;

private:

	Knight(char symbol, Color color, Type type)
		: Piece{ symbol, color, type }
	{
	}

	friend class PieceFactory;
};

#endif