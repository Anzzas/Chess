#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

class Bishop : public Piece
{
public:

	bool canMoveTo(const BoardState& board, const Position startPosition, const Position targetPosition) const override;

private:

	Bishop(char symbol, Color color, Type type)
		: Piece{ symbol, color, type }
	{
	}

	friend class PieceFactory;
};

#endif