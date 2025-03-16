#ifndef MOVE_H
#define MOVE_H
#include <optional>
#include "enums.h"
#include "position.h"

class Move
{
public:

	Move(Type fromType, Type toType, Position from, Position To, MoveType moveType)
		: m_fromType{ fromType }
		, m_toType{ toType }
		, m_from{ from }
		, m_to{ To }
		, m_moveType{ moveType }
	{
	}

	const Position& getFrom() const { return m_from; }
	const Position& getTo() const { return m_to; }
	const Type& getFromType() const { return m_fromType; }
	const Type& getCapturedType() const { return m_toType; }
	const MoveType& getMoveType() const { return m_moveType; }
	void setMoveType(MoveType moveType) { m_moveType = moveType; }

private:

	Type m_fromType{};
	Type m_toType{};
	Position m_from;
	Position m_to;
	MoveType m_moveType{};
	std::optional<Type> m_promotion;
	bool m_isCheck{};
	bool m_isCheckmate{};
};

#endif