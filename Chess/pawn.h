#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Board;

class Pawn : public Piece
{
public:

	bool canMoveTo(const Board& board, const std::pair<size_t, size_t> startPosition, const std::pair<size_t, size_t> targetPosition) const override;

	static void resetAllPawnFlags(const Board& b, Piece::Color color);
	const bool& hasMovedTwoSquares() const;
	void setHasMovedTwoSquares(bool state);

protected:

	Pawn(char symbol, Color color, Type type)
		: Piece{ symbol, color, type }
	{
	}

	friend class PieceFactory;

private:

	bool m_hasMovedTwoSquares{};
};

#endif