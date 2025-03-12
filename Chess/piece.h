#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <iostream>
#include <array>
#include <utility>
#include <cassert>
#include "enums.h"
#include "position.h"
#include "boardState.h"

class BoardState;

class Piece
{
public:

	Piece() = delete;
	virtual ~Piece() = default;

	const char& getSymbol() const;
	const Color& getColor() const;
	const Type& getType() const;
	virtual bool canMoveTo(const BoardState& board, const Position startPosition, const Position targetPosition) const = 0;

	friend std::ostream& operator<< (std::ostream& out, const Color& color);
	friend std::ostream& operator<< (std::ostream& out, const Piece& piece);
	Piece& operator= (const Piece& piece);

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