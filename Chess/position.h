#ifndef POSITION_H
#define POSITION_H
#include <optional>
#include "constants.h"

class Position
{
public:

	Position(size_t y, size_t x)
		: m_y{ y }
		, m_x{ x }
	{
	}

	bool isValid() const;
	bool isValid(int offsetY, int offsetX) const;
	std::optional<Position> offset(int offsetY, int offsetX) const;
	bool operator== (const Position& pos);
	Position& operator= (const Position& pos);
	const size_t& getX() const;
	const size_t& getY() const;

private:

	size_t m_y{};
	size_t m_x{};
};

#endif