#include "case.h"

std::ostream& operator<< (std::ostream& out, const Case& c)
{
	if (c.m_piece)
		out << *c.m_piece.get();

	else
		out << ".";

	return out;
}

void Case::setPiece(const Piece& piece)
{
	if (m_piece)
		std::cout << "Cannot add another piece !\n";

	else
		m_piece = std::make_unique<Piece>(piece);
}