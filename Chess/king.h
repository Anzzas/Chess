#ifndef KING_H
#define KING_H
#include "piece.h"

class King : public Piece
{
public:

	bool canMoveTo(const Board& board, const std::pair<size_t, size_t> startPosition, const std::pair<size_t, size_t> targetPosition) const override;
	const bool& getHasMoved() const;
	void setHasMoved(bool hasMoved);

private:

	King(char symbol, Color color, Type type)
		: Piece{ symbol, color, type }
	{
	}

	friend class PieceFactory;
	bool hasMoved{};
};

#endif