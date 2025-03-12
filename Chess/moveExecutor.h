#ifndef MOVEEXECUTOR_H
#define MOVEEXECUTOR_H
#include "board.h"

class MoveExecutor
{
public:

	void executeMove(Board& board, Position from, Position to);
	void executeCastling(Board& board, Color playerColor, CastlingSide side);
	void executePawnPromotion(Board& board, Position pawnPos, Type promotionType);
};

#endif