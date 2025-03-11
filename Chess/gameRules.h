#ifndef GAMERULES_H
#define GAMERULES_H
#include "moveValidator.h"

class GameRules
{
public:

	bool isKingInCheck(const BoardState& state, Color kingColor) const;
	bool isCheckmate(const BoardState& state, Color kingColor) const;
	bool isStalemate(const BoardState& state, Color kingColor) const;
};

#endif