#include "position.h"

bool Position::isValid() const
{
	if (m_x >= boardSettings::boardSizeMin && m_x < boardSettings::boardSize && m_y >= boardSettings::boardSizeMin && m_y < boardSettings::boardSize)
		return true;

	return false;
}

bool Position::isValid(int offsetY, int offsetX) const
{
	return offsetY + m_y >= boardSettings::boardSizeMin && offsetY < boardSettings::boardSize && offsetX + m_x >= boardSettings::boardSizeMin && offsetX < boardSettings::boardSize;
}

std::optional<Position> Position::offset(int offsetY, int offsetX) const
{
	if (isValid(offsetY, offsetX))
		return Position{ static_cast<size_t>(offsetY) + m_y, static_cast<size_t>(offsetX) + m_x };

	return std::nullopt;
}
 
bool Position::operator== (const Position& pos)
{
	return pos.m_x == m_x && pos.m_y == m_y;
}

Position& Position::operator= (const Position& pos)
{
	this->m_x = pos.m_x;
	this->m_y = pos.m_y;

	return *this;
}

const size_t& Position::getX() const
{
	return m_x;
}

const size_t& Position::getY() const
{
	return m_y;
}