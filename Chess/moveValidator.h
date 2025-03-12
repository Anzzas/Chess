#ifndef MOVEVALIDATOR_H
#define MOVEVALIDATOR_H

class MoveValidator
{
public:

	bool isValidMove(const BoardState& board, Position from, Position to) const;
	bool wouldLeaveKingInCheck(const BoardState& board, Position from, Position to, Piece::Color playerColor) const;
};

#endif