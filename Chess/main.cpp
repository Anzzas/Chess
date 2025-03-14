#include "pieceFactory.h"
#include "userInput.h"
#include "gamestate.h"

int main()
{
	std::cout << "\tChess Game\n\n";
	
	UserInput userinput{};

	userinput.inputMove()

	GameState game{};
	game.makeMove();
	std::cout << board << "\n\n";
	Color playerTurn{ white };

	while (true)
	{
		const auto startCase{ inputInitialCase(board, playerTurn) };
		const auto startCaseY{ startCase.getY() };
		const auto startCaseX{ startCase.getX() };

		std::optional<Position> targetCase{ {0, 0} };
		auto targetCaseY{ targetCase->getY() };
		auto targetCaseX{ targetCase->getX() };

		if (g_isCastling) // If player is castling
		{
			std::cout << "Castling\n\n";
			targetCase = startCase; // Putting selected rook on targetCase for check/check mate verification
			targetCaseY = targetCase->getY();
			targetCaseX = targetCase->getX();
		}

		else
		{
			targetCase = inputTargetCase(board, startCase, playerTurn);

			if (!targetCase)
			{
				std::cout << "This Piece cannot defend the king. Please choose another piece.\n\n";
				continue;
			}

			targetCaseY = targetCase->getY();
			targetCaseX = targetCase->getX();

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

		if (board.isCheckMate(board.getBoard()[targetCaseY][targetCaseX].getPiece().getColor() == black ? white : black))
		{
			std::cout << "CHECK MATE !\n\n";
			return 0;
		}

		else if (board.isKingInCheck(board.getBoard()[targetCaseY][targetCaseX].getPiece().getColor() == black ? white : black))
			std::cout << "CHECK !\n\n";

		// Changing player turn to the opposite color after the turn is finished
		playerTurn == white ? playerTurn = black : playerTurn = white;

		std::cout << "It is ";
		switch (playerTurn)
		{
		case white:
			std::cout << "white";
			break;
		case black:
			std::cout << "black";
			break;
		}
		std::cout << " turn!\n\n";

		if (g_isCastling)
			g_isCastling = false; // Reseting castling state

		// Reseting en-passant flags of the next player to play
		Pawn::resetAllPawnFlags(board, playerTurn);
	}
 }