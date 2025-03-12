#include "case.h"
#include "piece.h"

std::ostream& operator<< (std::ostream& out, const Case& c)
{
	if (c.m_piece)
		out << *c.m_piece.get();

	else
		out << ".";

	return out;
}

std::unique_ptr<Piece>& Case::getCase()
{
	return m_piece;
}

void Case::setPiece(std::unique_ptr<Piece> piece)
{
	if (m_piece)
		std::cout << "Cannot add another piece !\n";

	if (piece)
		m_piece = std::move(piece);
	else  
		m_piece = nullptr;
}

bool Case::isEmpty() const
{
	return m_piece ? false : true;
}

const Piece& Case::getPiece() const
{
	return *m_piece.get();
}

const std::unique_ptr<Piece>& Case::getCase() const
{
	return m_piece;
}