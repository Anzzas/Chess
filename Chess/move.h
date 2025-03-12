#ifndef MOVE_H
#define MOVE_H
#include <optional>

class Position;

class Move
{
public:

private:
	Type pieceType;
	Type capturedType;
	Position from;
	Position to;
	std::optional<Piece::Type> promotion;
	bool isCheck;
	bool isCheckmate;
	bool isCastling;
	bool isEnPassant;
};

#endif