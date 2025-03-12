#ifndef BOARDSTATE_H
#define BOARDSTATE_H
#include "position.h"
#include "enums.h"

class Piece;

inline std::map<std::string, Position> choiceToCoord = []()
	{
		std::map<std::string, Position> result;
		std::string cols{ "abcdefgh" };

		for (size_t x{}; x < cols.size(); x++)
		{
			for (size_t y{}; y < cols.size(); y++)
			{
				std::string key{ cols[x] };
				key += std::to_string(y + 1);
				result.try_emplace(key, Position{ (boardSettings::boardSize - 1) - y, x });
			}
		}

		return result;

	}();

class BoardState
{
public:

	~BoardState() = default;

	virtual bool isEmpty(Position pos) const = 0;
	virtual const Piece* getPieceAt(Position pos) const = 0;
	virtual bool isPositionUnderAttack(Position pos, Color attackerColor) const = 0;
	virtual const Position& getKingPosition(Color color) const = 0;
};

#endif