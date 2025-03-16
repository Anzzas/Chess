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
	virtual const Type& getPieceTypeAt(Position pos) const = 0;
	virtual const Color& getPieceColorAt(Position pos) const = 0;
	virtual bool isPositionUnderAttack(Position pos, Color attackerColor) const = 0;
	virtual const Position& getKingPosition(Color color) const = 0;
	virtual bool isPieceOfColor(Position pos, Color color) const = 0;
	virtual bool isSquareUnderAttackAt(Position pos, Color attacker) const = 0;
	virtual std::vector<Position> getSquaresBetween(const Position& from, const Position& to) const = 0;
};

#endif