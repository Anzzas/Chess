#include <iostream>
#include "pieceFactory.h"
#include "board.h"
#include <string>
#include <map>
#include <utility>
#include <iterator>

std::pair<size_t, size_t> inputInitialCase(const Board& board)
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

		else if (board.getBoard()[y][x].getPiece().getColor() == Piece::black)
		{
			std::cout << "Select one of your white pieces!\n\n";
			continue;
		}
		break;
	}
	return std::pair{ y, x };
}

std::pair<size_t, size_t> inputTargetCase(const Board& board)
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
		const Case& targetCase = board.getBoard()[y][x];

		if (targetCase.isEmpty() || targetCase.getPiece().getColor() == Piece::black)
			break;

		else if (targetCase.getPiece().getColor() == Piece::white)
		{
			std::cout << "There is already a white piece here !\n\n";
			continue;
		}
	}
	return std::pair{ y, x };
}

int main()
{
	std::cout << "\tChess Game\n" << "You are playing white pieces !\n\n";
	
	Board board{};
	std::cout << board << "\n\n";

	while (true)
	{

		std::pair startCase{ inputInitialCase(board) };
		std::pair targetCase{ inputTargetCase(board) };
		const Piece& choosenPiece{ board.getBoard()[startCase.first][startCase.second].getPiece() };

		if (!choosenPiece.canMoveTo(board, startCase, targetCase))
		{
			std::cout << choosenPiece << " cannot move here!\n\n";
			continue;
		}
			board.movePiece(startCase, targetCase);

			if (board.isKingInCheck(Piece::black))
			{
				std::cout << "CHECK !\n\n";
			}

			std::cout << board << "\n\n"; 
	}
}