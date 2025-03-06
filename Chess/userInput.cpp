#include "userInput.h"

std::pair<size_t, size_t> inputInitialCase(Board& board, const Piece::Color playerColor)
{
	size_t x{};
	size_t y{};
	std::string choice{};
	while (true)
	{

		std::cout << "Select the piece you want to play: ";
		std::cin >> choice;

		if (choice == "oq" && board.canCastleLeft(playerColor))
		{
			board.castle(playerColor, choice);
			return { 21, 21 }; // Sentinel value code for castling
		}
		else if (choice == "oo" && board.canCastleRight(playerColor))
		{
			board.castle(playerColor, choice);
			return { 21, 21 }; // Sentinel value code for castling
		}


		if (!boardSettings::choiceToCoord.contains(choice))
		{
			std::cout << "Enter a valid case !\n\n";
			continue;
		}

		x = static_cast<size_t>(boardSettings::choiceToCoord.find(choice)->second.second);
		y = static_cast<size_t>(boardSettings::choiceToCoord.find(choice)->second.first);

		if (board.getBoard()[y][x].isEmpty())
		{
			std::cout << "This case is empty !\n\n";
			continue;
		}

		else if (board.getBoard()[y][x].getPiece().getColor() != playerColor)
		{
			std::cout << "Select one of your ";
			switch (playerColor)
			{
			case Piece::white:
				std::cout << "white";
				break;
			case Piece::black:
				std::cout << "black";
				break;
			}
			std::cout << " pieces!\n\n";
			continue;
		}

		break;
	}
	return std::pair{ y, x };
}

std::pair<size_t, size_t> inputTargetCase(const Board& board, const Piece::Color playerColor)
{
	size_t x{};
	size_t y{};
	std::string choice{};
	while (true)
	{
		std::cout << "Select the target case: ";
		std::cin >> choice;

		if (!boardSettings::choiceToCoord.contains(choice))
		{
			std::cout << "Enter a valid case !\n\n";
			continue;
		}

		x = static_cast<size_t>(boardSettings::choiceToCoord.find(choice)->second.second);
		y = static_cast<size_t>(boardSettings::choiceToCoord.find(choice)->second.first);
		const std::pair<size_t, size_t> targetCoord{ y, x };
		const Case& targetCase = board.getBoard()[y][x];

		if (!targetCase.isEmpty() && targetCase.getPiece().getColor() == playerColor)
		{
			std::cout << "There is already a ";
			switch (playerColor)
			{
			case Piece::white:
				std::cout << "white";
				break;
			case Piece::black:
				std::cout << "black";
				break;
			}
			std::cout << " piece here !\n\n";
			continue;
		}

		else if (board.isKingInCheck(playerColor))
		{
			std::pair kingPosition{ board.getKingPosition(playerColor) };
			std::pair attackerPosition{ board.getAttackingPieceCoord(playerColor == Piece::black ? Piece::white : Piece::black) };
			std::vector<std::pair<size_t, size_t>> path = board.findAttackPath(attackerPosition, kingPosition);

			if (targetCoord == attackerPosition)
				return targetCoord;

			for (const auto& e : path)
			{
				if (targetCoord == e)
					return targetCoord;
			}

			return std::pair<size_t, size_t> {boardSettings::boardSize, boardSettings::boardSize}; // Sentinel value in order if the selected piece can't defend the KING
		}

		else if (targetCase.isEmpty() || targetCase.getPiece().getColor() != playerColor)
			break;
	}
	return std::pair{ y, x };
}