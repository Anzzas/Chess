#include "pieceFactory.h"
#include "userInput.h"

int main()
{
	std::cout << "\tChess Game\n\n";
	
	Board board{};
	std::cout << board << "\n\n";
	Piece::Color playerTurn{ Piece::white };

	while (true)
	{
		const auto startCase{ inputInitialCase(board, playerTurn) };
		const auto [startCaseY, startCaseX] = startCase;

		std::optional<std::pair<size_t, size_t>> targetCase{ {} };
		auto [targetCaseY, targetCaseX] = *targetCase;

		if (g_isCastling) // If player is castling
		{
			std::cout << "Castling\n\n";
			targetCase = startCase; // Putting selected rook on targetCase for check/check mate verification
			targetCaseY = targetCase->first;
			targetCaseX = targetCase->second;
		}

		else
		{
			targetCase = inputTargetCase(board, startCase, playerTurn);

			if (!targetCase)
			{
				std::cout << "This Piece cannot defend the king. Please choose another piece.\n\n";
				continue;
			}

			targetCaseY = targetCase->first;
			targetCaseX = targetCase->second;

			const auto& choosenPiece{ board.getBoard()[startCaseY][startCaseX].getPiece() };
			if (!choosenPiece.canMoveTo(board, startCase, *targetCase))
			{
				std::cout << choosenPiece << " cannot move here!\n\n";
				continue;
			}

			if (board.isSelfCheck(startCase, *targetCase, playerTurn)) // if player self check, he has to try again
			{
				std::cout << "You cannot do this move (self check) !\n\n";
				continue;
			}

			board.movePiece(startCase, *targetCase);
		}

		std::cout << board << "\n\n";

		if (board.isCheckMate(board.getBoard()[targetCaseY][targetCaseX].getPiece().getColor() == Piece::black ? Piece::white : Piece::black))
		{
			std::cout << "CHECK MATE !\n\n";
			return 0;
		}

		else if (board.isKingInCheck(board.getBoard()[targetCaseY][targetCaseX].getPiece().getColor() == Piece::black ? Piece::white : Piece::black))
			std::cout << "CHECK !\n\n";

		// Changing player turn to the opposite color after the turn is finished
		playerTurn == Piece::white ? playerTurn = Piece::black : playerTurn = Piece::white;

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

		if (g_isCastling)
			g_isCastling = false; // Reseting castling state
	}
 }