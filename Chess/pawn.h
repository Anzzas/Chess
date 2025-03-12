#ifndef PAWN_H
#define PAWN_H
#include "piece.h"
#include "case.h"

class Board;

class Pawn : public Piece
{
public:

	bool canMoveTo(const BoardState& board, const Position startPosition, const Position targetPosition) const override;

	static void resetAllPawnFlags(const BoardState& b, Color color);
	const bool& hasMovedTwoSquares() const;
	void setHasMovedTwoSquares(bool state) const;
	const bool& hasUsedEnPassant() const;
	void setHasUsedEnPassant(bool state) const;

protected:

	Pawn(char symbol, Color color, Type type)
		: Piece{ symbol, color, type }
	{
	}

	friend class PieceFactory;

private:

	mutable bool m_hasMovedTwoSquares{};
	mutable bool m_hasUsedEnPassant{};
};

#endif