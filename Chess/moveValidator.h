#ifndef MOVEVALIDATOR_H
#define MOVEVALIDATOR_H
#include "boardState.h"
#include "pieceFactory.h"

class MoveValidator
{
public:

	bool isValidMove(const BoardState& board, Position from, Position to) const;
	bool wouldLeaveKingInCheck(const BoardState& board, Position from, Position to, Color playerColor) const;
};

#endif