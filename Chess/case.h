#ifndef CASE_H
#define CASE_H
#include <memory>

class Piece;

class Case
{
public:

	Case() = default;
	Case(Case&) = delete;
	Case(Case&&) = delete;

	const Piece& getPiece() const;
	std::unique_ptr<Piece>& getCase();
	const std::unique_ptr<Piece>& getCase() const;

	friend std::ostream& operator<< (std::ostream& out, const Case& c);
	void setPiece(std::unique_ptr<Piece> piece);
	bool isEmpty() const;

private:

	std::unique_ptr<Piece> m_piece;
};

#endif