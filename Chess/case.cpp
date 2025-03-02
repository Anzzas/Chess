#include "case.h"

std::ostream& operator<< (std::ostream& out, const Case& c)
{
	if (c.m_case)
		out << *c.m_case.get();

	else
		out << ".";

	return out;
}

std::unique_ptr<Piece>& Case::getCase()
{
	return m_case;
}

void Case::setPiece(std::unique_ptr<Piece> piece)
{
	if (m_case)
		std::cout << "Cannot add another piece !\n";

	if (piece)
		m_case = std::move(piece);
	else
		m_case = nullptr;
}

bool Case::isEmpty() const
{
	return m_case ? false : true;
}

const Piece& Case::getPiece() const
{
	return *m_case.get();
}

void Case::replacePiece(std::unique_ptr<Piece>& startingCase)
{
		m_case = std::move(startingCase);
}

void Case::deletePiece() { m_case.reset(); }