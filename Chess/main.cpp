#include <iostream>
#include "pieceFactory.h"
#include "board.h"
#include <string>
#include <map>
#include <utility>
#include <iterator>

std::pair<size_t, size_t> inputInitialCase(const Board& board, const Piece::Color playerColor)
{
	size_t x{};
	size_t y{};
	std::string choice{};
	while (true)
	{

		std::cout << "Select the piece you want to play: ";
		std::cin >> choice;

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

int main()
{
	std::cout << "\tChess Game\n";
	
	Board board{};
	std::cout << board << "\n\n";
	Piece::Color playerTurn{ Piece::white };

	while (true)
	{
		std::pair startCase{ inputInitialCase(board, playerTurn) };
		std::pair targetCase{ inputTargetCase(board, playerTurn) };

		if (targetCase == std::pair<size_t, size_t> {boardSettings::boardSize, boardSettings::boardSize})
		{
			std::cout << "This Piece cannot defend the king. Please choose another piece.\n\n";
			continue;
		}

		const Piece& choosenPiece{ board.getBoard()[startCase.first][startCase.second].getPiece() };

		if (!choosenPiece.canMoveTo(board, startCase, targetCase))
		{
			std::cout << choosenPiece << " cannot move here!\n\n";
			continue;
		}
			board.movePiece(startCase, targetCase);

			if (board.isCheckMate(choosenPiece.getColor() == Piece::black ? Piece::white : Piece::black))
			{
				std::cout << "CHECK MATE !\n\n";
				return 0;
			}

			std::cout << board << "\n\n";

			std::cout << "It is ";
			switch (playerTurn)
			{
			case Piece::white:
				std::cout << "white";
				break;
			case Piece::black:
				std::cout << "black";
				break;
			}
			std::cout << " turn!\n\n";

			if (board.isKingInCheck(choosenPiece.getColor() == Piece::black ? Piece::white : Piece::black))
				std::cout << "CHECK !\n\n";

			playerTurn = playerTurn == Piece::white ? Piece::black : Piece::white;
	}
}