#include "piece.h"
#include <cctype>

char getLowerChar(char c)
{
	return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
}

const char& Piece::getSymbol() const
{
	return m_symbol;
}

const Piece::Color& Piece::getColor() const
{
	return m_color;
}

const Piece::Type& Piece::getType() const
{
	return m_type;
}

std::ostream& operator<< (std::ostream& out, const Piece& piece)
{
	if (piece.getColor() == Piece::black)
		out << getLowerChar(piece.getSymbol()); // Printing piece's symbol in lower case for BLACK

	else
		out << piece.getSymbol(); // Printing in upper case for WHITE

	return out;
}

std::ostream& operator<< (std::ostream& out, const Piece::Color& color)
{
	constexpr std::array<const char, Piece::max_colors> colors{ 'w', 'b' };
	static_assert(colors.size() == Piece::max_colors);

	out << colors[color];
	return out;
}

Piece& Piece::operator= (const Piece& piece)
{
	m_symbol = piece.m_symbol;
	m_color = piece.m_color;
	m_type = piece.m_type;

	return *this;
}