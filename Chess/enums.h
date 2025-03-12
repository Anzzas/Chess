#ifndef ENUMS_H
#define ENUMS_H

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

	enum class CastlingSide
	{
		left,
		right,
		max_sides
	};

#endif