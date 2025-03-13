#ifndef BOARDSTATE_H
#define BOARDSTATE_H
#include "position.h"
#include "enums.h"

class Piece;

class BoardState
{
public:

	~BoardState() = default;

	virtual bool isEmpty(Position pos) const = 0;
	virtual const Piece* getPieceAt(Position pos) const = 0;
	virtual bool isPositionUnderAttack(Position pos, Color attackerColor) const = 0;
	virtual const Position& getKingPosition(Color color) const = 0;
};

#endif