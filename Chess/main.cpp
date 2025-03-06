#include "pieceFactory.h"
#include "userInput.h"

int main()
{
	std::cout << "\tChess Game\n";
	
	Board board{};
	std::cout << board << "\n\n";
	Piece::Color playerTurn{ Piece::white };

	while (true)
	{
		std::pair startCase{ inputInitialCase(board, playerTurn) };

		if (startCase == std::pair{ 21, 21 }) // If player is castling
		{

			std::cout << "Castling\n\n";
			continue;
		}

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

		if (board.isSelfCheck(startCase, targetCase, playerTurn)) // if player self check, he has to try again
		{
			std::cout << "You cannot do this move (self check) !\n\n";
			continue;
		}

		if (board.isCheckMate(board.getBoard()[targetCase.first][targetCase.second].getPiece().getColor() == Piece::black ? Piece::white : Piece::black))
		{
			std::cout << "CHECK MATE !\n\n";
			return 0;
		}

		std::cout << board << "\n\n";

		if (board.isKingInCheck(board.getBoard()[targetCase.first][targetCase.second].getPiece().getColor() == Piece::black ? Piece::white : Piece::black))
			std::cout << "CHECK !\n\n";

		playerTurn = playerTurn == Piece::white ? Piece::black : Piece::white;

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
	}
 }