#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Board;

class Pawn : public Piece
{
public:

	bool canMoveTo(const Board& board, const std::pair<size_t, size_t> startPosition, const std::pair<size_t, size_t> targetPosition) const override;

protected:

	Pawn(char symbol, Color color, Type type)
		: Piece{ symbol, color, type }
	{
	}

	friend class PieceFactory;
};

#endif