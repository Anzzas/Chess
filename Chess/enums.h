#ifndef ENUMS_H
#define ENUMS_H

	enum class Color
	{
		white,
		black,
		max_colors
	};

	enum class Type
	{
		pawn,
		bishop,
		knight,
		rook,
		queen,
		king,
		null_type,
		max_types
	};

	enum class CastlingSide
	{
		left,
		right,
		max_sides
	};

	enum class MoveType
	{
		normal,
		castling,
		promotion,
		enPassant,
		max_moveTypes,
	};

#endif