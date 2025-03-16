#include "userInput.h"

using enum MoveType;
using enum Color;
using enum Type;

Move UserInput::inputMoves(const BoardState& board, const Color& playerColor) const
{
	std::string firstChoice{ setUserInput(board, playerColor, ValidationMode::InitialSquare) };

	if (isCastlingMove(firstChoice))
		return getCastlingMove(firstChoice, playerColor, board);

	std::string secondChoice{ setUserInput(board, playerColor, ValidationMode::TargetSquare) };

	Position from{ inputToPosition(firstChoice) };
	Position to{ inputToPosition(secondChoice) };

	Type fromType{ board.getPieceTypeAt(from) };
	Type toType{ board.getPieceTypeAt(to) };

	return { fromType, toType, from, to, normal };
}

std::string UserInput::setUserInput(const BoardState& board, const Color playerColor, ValidationMode mode) const
{
	std::string choice{};

	while (true)
	{
		switch (mode)
		{
		case ValidationMode::InitialSquare:
			std::cout << "Select a piece of yours: ";
			break;
		case ValidationMode::TargetSquare:
			std::cout << "Target square: ";
			break;
		}

		std::cin >> choice;

		if (isChoiceValid(choice, board, playerColor, mode))
			return choice;
	}
}

Move UserInput::getCastlingMove(std::string_view input, Color playerColor, const BoardState& board) const
{
	size_t y_rook{ playerColor == white ? 7 : 0 };
	size_t x_rook{ input == "oq" ? 0 : 7 };

	Position rookPosition{ y_rook, x_rook }; 
	Position kingPosition{ board.getKingPosition(playerColor) };

	return { rook, king, rookPosition, kingPosition, castling };
}

bool UserInput::isChoiceValid(const std::string& choice, const BoardState& board, Color playerColor, ValidationMode mode) const
{
	/*if (choice == "oq" || choice == "oo")
	{
		if (choice == "oq" && board.canCastleLeft(playerColor))
		{
			g_isCastling = true;
			return board.castle(playerColor, choice);
		}
		else if (choice == "oo" && board.canCastleRight(playerColor))
		{
			g_isCastling = true;
			return board.castle(playerColor, choice);
		}

		std::cout << "You cannot castle ";
		if (choice == "oq")
			std::cout << "left ";
		else if (choice == "oo")
			std::cout << "right ";

		std::cout << "!\n\n";
		continue;
	}*/

	if (!choiceToCoord.contains(choice))
	{
		std::cout << "Enter a valid case !\n\n";
		return false;
	}
	const Position pos{ choiceToCoord.find(choice)->second };

	if (board.isEmpty(pos))
	{
		std::cout << "This case is empty !\n\n";
		return false;
	}

	switch (mode)
	{
	case ValidationMode::InitialSquare:

		if (!board.isPieceOfColor(pos, playerColor))
		{
			std::cout << "Select one of your ";
			switch (playerColor)
			{
			case white:
				std::cout << "white";
				break;
			case black:
				std::cout << "black";
				break;
			}
			std::cout << " pieces!\n\n";
			return false;
		}
		break;

	case ValidationMode::TargetSquare:

		if (!board.isEmpty(pos) && board.isPieceOfColor(pos, playerColor))
		{
			std::cout << "There is already a ";
			switch (playerColor)
			{
			case white:
				std::cout << "white";
				break;
			case black:
				std::cout << "black";
				break;
			}
			std::cout << " piece here !\n\n";
			return false;;
		}
	}
	return true;
}

Position UserInput::inputToPosition(const std::string& input) const { return choiceToCoord.find(input)->second; }

bool UserInput::isCastlingMove(std::string_view choice) const { return choice == "oq" || choice == "oo"; }