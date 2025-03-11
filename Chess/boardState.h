#ifndef BOARDSTATE_H
#define BOARDSTATE_H

class Position;
class Piece;

class BoardState
{
public:

	bool isEmpty(Position pos) const;
	const Piece* getPieceAt(Position pos) const;
	bool isPositionUnderAttack(Position pos, Piece::Color attackerColor) const;
	const Position& getKingPosition(Piece::Color color) const;
};

#endif