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

		// Castling CHECK
		if (choice == "oq" || choice == "oo")
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

std::optional<std::pair<size_t, size_t>> inputTargetCase(Board& board, const std::pair<size_t, size_t> startCase, const Piece::Color playerColor)
{
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
		const auto targetCoord{boardSettings::choiceToCoord.find(choice)->second};
		const auto [targetY, targetX] = targetCoord;
		const Case& targetCase = board.getBoard()[targetY][targetX];

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
			const auto kingPosition{ board.getKingPosition(playerColor) };
			const auto attackerPosition{ board.getAttackingPieceCoord(playerColor == Piece::black ? Piece::white : Piece::black) }; 

			if (!attackerPosition)
				throw std::runtime_error{ "King in check but no attacker found !" };

			// Getting the attack path
			const auto path = board.findAttackPath(*attackerPosition, kingPosition);

			// Checking if the target selected case is the King attacker (meaning the player decide to take that piece)
			if (targetCoord == attackerPosition)
				return targetCoord;

			// Checking if the target selected case is corresponding to one of the attackPath (meaning it will block the king attack and cover him)
			for (const auto& attackedCase : path)
			{
				if (targetCoord == attackedCase)
					return targetCoord;
			}

			const auto [startCaseY, startCaseX] = startCase;
			const auto& startPiece{ board.getBoard()[startCaseY][startCaseX].getPiece() };

			if (startPiece.getType() == Piece::king && startPiece.canMoveTo(board, startCase, targetCoord))
				return targetCoord;

			
			return {}; // Returning nullopt because used move do not defend the king currently in check
		}

		else if (targetCase.isEmpty() || targetCase.getPiece().getColor() != playerColor)
			return std::pair{ targetY, targetX };

		throw std::runtime_error{ "Bad Input" };
	}
}