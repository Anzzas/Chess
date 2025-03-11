#ifndef MOVEHISTORY_H
#define MOVEHISTORY_H
#include <vector>
#include "gamestate.h"

class MoveHistory
{
public:

	void addMove(const Move& move);
	const Move& getLastMove() const;
private:

	std::vector<Move> moves;
};

#endif