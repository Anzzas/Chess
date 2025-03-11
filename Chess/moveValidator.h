#ifndef MOVEVALIDATOR_H
#define MOVEVALIDATOR_H
#include "boardState.h"
#include "board.h"

class MoveValidator
{
public:

	bool isValidMove(const BoardState& board, Position from, Position to) const;
	bool wouldLeaveKingInCheck(const BoardState& board, Position from, Position to, Piece::Color playerColor) const;
};

#endif