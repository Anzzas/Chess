#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "gamestate.h"

class UserInterface
{
public:

	void displayBoard(const BoardState& board) const;
	std::optional<Move> getPlayerMove(const GameState& game, Piece::Color player) const;
};

#endif