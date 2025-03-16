#ifndef USERINPUT_H
#define USERINPUT_H
#include "position.h"
#include "boardState.h"
#include "move.h"
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
	InitialSquare,
	TargetSquare
};

class UserInput
{
public:

	UserInput() = default;

	Move inputMoves(const BoardState& board, const Color& playerColor) const;

private:

	std::string setUserInput(const BoardState& board, const Color playerColor, ValidationMode mode) const;
	bool isChoiceValid(const std::string& choice, const BoardState& board, Color playerColor, ValidationMode mode) const;
	bool isCastlingMove(std::string_view choice) const;
	Position inputToPosition(const std::string& input) const;
	Move getCastlingMove(std::string_view input, Color playerColor, const BoardState& board) const;
};

#endif