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

	const Piece& getPiece() const;
	friend std::ostream& operator<< (std::ostream& out, const Case& c);
	void setPiece(std::unique_ptr<Piece> piece);
	bool isEmpty() const;
	void replacePiece(std::unique_ptr<Piece>& piece);
	void deletePiece();
	std::unique_ptr<Piece>& getCase();

private:

	std::unique_ptr<Piece> m_case;
};

#endif