#ifndef MOVE_H
#define MOVE_H
#include "position.h"
#include "moveHistory.h"
#include <optional>

class Move
{
public:

private:
	Piece::Type pieceType;
	Piece::Type capturedType;
	Position from;
	Position to;
	std::optional<Piece::Type> promotion;
	bool isCheck;
	bool isCheckmate;
	bool isCastling;
	bool isEnPassant;
};

#endif