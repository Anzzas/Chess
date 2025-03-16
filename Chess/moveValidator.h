#ifndef MOVEVALIDATOR_H
#define MOVEVALIDATOR_H
#include "boardState.h"
#include "pieceFactory.h"
#include "move.h"
#include <vector>

class MoveValidator
{
public:

	bool isValidMove(const BoardState& board, const Move& move, Color playerColor) const;
	bool wouldLeaveKingInCheck(const BoardState& board, Position from, Position to, Color playerColor) const;
	MoveType determineMoveType(const BoardState& board, const Move& move, Color playerColor) const;

private:

	bool isPromotionMove(const BoardState& board, const Move& move, Color playerColor) const;
	bool isEnPassantMove(const BoardState& board, const Move& move, Color playerColor) const;
	bool validateNormalMove(const BoardState& board, const Move& move, Color playerColor) const;
	bool validateCastlingMove(const BoardState& board, const Move& move, Color playerColor) const;
	bool validateEnPassantMove(const BoardState& board, const Move& move, Color playerColor) const;
	bool validatePromotionMove(const BoardState& board, const Move& move, Color playerColor) const;
};

#endif