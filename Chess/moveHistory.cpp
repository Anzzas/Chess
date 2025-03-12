#include "moveHistory.h"

void MoveHistory::addMove(const Move& move)
{
	m_moves.emplace_back(move);
}

const Move& MoveHistory::getLastMove() const
{
	return m_moves.back();
}