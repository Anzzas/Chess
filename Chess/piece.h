#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <iostream>
#include <array>
#include <utility>

class Board;

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
	virtual bool canMoveTo(const Board& board, const std::pair<size_t, size_t> startPosition, const std::pair<size_t, size_t> targetPosition) const = 0;

	friend std::ostream& operator<< (std::ostream& out, const Color& color);
	friend std::ostream& operator<< (std::ostream& out, const Piece& piece);
	Piece& operator= (const Piece& piece);
	bool isSameColor(const Piece& piece) const;

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