#ifndef MOVEHISTORY_H
#define MOVEHISTORY_H
#include <vector>

class Move;

class MoveHistory
{
public:

	void addMove(const Move& move);
	const Move& getLastMove() const;
private:

	std::vector<Move> m_moves;
};

#endif