#ifndef CASE_H
#define CASE_H
#include <memory>
#include "piece.h"

class Case
{
public:

	Case() = default;
	Case(Case&) = delete;
	Case(Case&&) = delete;

	friend std::ostream& operator<< (std::ostream& out, const Case& c);
	void setPiece(std::unique_ptr<Piece> piece);

private:

	std::unique_ptr<Piece> m_piece;
};

#endif