#include "userInput.h"

std::pair<Position, Position> UserInput::inputMove(const BoardState& board, const Color playerColor) const
{
	return { inputInitialCase(board, playerColor), inputTargetCase(board, playerColor) };
}

Position UserInput::inputInitialCase(const BoardState& board, const Color playerColor) const
{
	std::string choice{};
	while (true)
	{
		std::cout << "Select the piece you want to play: ";
		std::cin >> choice;

		if (isChoiceValid(choice, board, playerColor, ValidationMode::InitialPiece))
			break;
	}

	return choiceToCoord.find(choice)->second;
}

Position UserInput::inputTargetCase(const BoardState& board, const Color playerColor) const
{
	std::string choice{};
	while (true)
	{
		std::cout << "Select the target case: ";
		std::cin >> choice;

		if (isChoiceValid(choice, board, playerColor, ValidationMode::TargetPiece))
			break;
	}

	return Position{ choiceToCoord.find(choice)->second };
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
	case ValidationMode::InitialPiece:

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

	case ValidationMode::TargetPiece:

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