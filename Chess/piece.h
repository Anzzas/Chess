#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <ostream>

class Piece
{
public:

	enum Color
	{
		white,
		black,
		max_colors
	};

	enum Type
	{
		pawn,
		bishop,
		knight,
		rook,
		queen,
		king,
		max_types
	};

	Piece() = delete;
	virtual ~Piece() = default;

	const char& getSymbol() const;
	const Color& getColor() const;
	const Type& getType() const;
	virtual void move() const = 0;

	friend std::ostream& operator<< (std::ostream& out, const Piece& piece);
	bool operator== (const Piece& piece) const;

protected:

	Piece(char symbol, Color color, Type type)
		: m_symbol{ symbol }, m_color{ color }, m_type{ type }
	{
	}

	char m_symbol;
	Color m_color;
	Type m_type;

};

#endif