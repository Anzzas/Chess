#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook : public Piece
{
public:

	bool canMoveTo(const BoardState& board, const Position startPosition, const Position targetPosition) const override;
	const bool& getHasMoved() const;
	void setHasMoved(bool hasMoved);

private:

	Rook(char symbol, Color color, Type type)
		: Piece{ symbol, color, type }
	{
	}

	friend class PieceFactory;
	bool hasMoved{};
};

#endif