#ifndef USERINPUT_H
#define USERINPUT_H
#include "position.h"
#include "boardState.h"
#include <iostream>

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


enum class ValidationMode
{
	InitialPiece,
	TargetPiece
};

inline bool g_isCastling{};

class UserInput
{
public:

	UserInput() = default;

	std::pair<Position, Position> inputMove(const BoardState& board, const Color playerColor) const;

private:

	Position inputInitialCase(const BoardState& board, const Color playerColor) const;
	Position inputTargetCase(const BoardState& board, const Color playerColor) const;
	bool isChoiceValid(const std::string& choice, const BoardState& board, Color playerColor, ValidationMode mode) const;
};

#endif