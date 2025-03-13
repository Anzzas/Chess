#ifndef MOVE_H
#define MOVE_H
#include <optional>
#include "enums.h"
#include "position.h"

class Move
{
public:

	Move(Type pieceType, Type capturedType, Position from, Position To)
		: m_usedType{pieceType}
		, m_capturedType{capturedType}
		, m_from{from}
		, m_to{To}
	{
	}

	const Position& getFrom() const { return m_from; }
	const Position& getTo() const { return m_to; }
	const Type& getUsedType() const { return m_usedType; }
	const Type& getCapturedType() const { return m_capturedType; }

private:

	Type m_usedType;
	Type m_capturedType;
	Position m_from;
	Position m_to;
	std::optional<Type> m_promotion;
	bool m_isCheck;
	bool m_isCheckmate;
	bool m_isCastling;
	bool m_isEnPassant;
};

#endif