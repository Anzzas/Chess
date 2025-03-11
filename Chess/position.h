#ifndef POSITION_H
#define POSITION_H

class Position
{
public:

	Position(size_t y, size_t x)
		: m_y{ y }
		, m_x{ x }
	{
	}

	bool isValid() const;
	Position offset(int rowOffset, int colOffset) const;
	bool operator== (const Position& pos);
	Position& operator= (const Position& pos);

private:

	size_t m_y{};
	size_t m_x{};
};

#endif