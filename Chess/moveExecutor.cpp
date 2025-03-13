#include "moveExecutor.h"

void MoveExecutor::executeMove(Board& board, Position from, Position to)
{
	const auto toY{ to.getY() };
	const auto toX{ to.getX() };

	const Piece* startPiece{ board.getPieceAt(from)};
	const Piece* targetPiece{ board.getPieceAt(to) };

	if (!startPiece)
		throw std::runtime_error{ "Undefined startPiece" };

	targetPiece = std::move(startPiece);

	// For EN-PASSANT
	if (targetPiece->getType() == pawn && dynamic_cast<Pawn*>(targetPiece)->hasUsedEnPassant())
	{
		const int direction{ targetPiece->getColor() == white ? 1 : -1 };
		const int newY{ static_cast<int>(toY) + direction };

		board.removePieceAt({ static_cast<size_t>(newY), toX });
		dynamic_cast<Pawn*>(targetPiece)->setHasUsedEnPassant(false);
		return;
	}

	// Promotion check. If the moved piece is of type Pawn and on Y = 0 (for WHITE) OR Y = 7 (for BLACK), then allow promotion
	if (targetPiece->getType() == pawn && ((targetPiece->getColor() == white && toY == 0) || (targetPiece->getColor() == black && toY == 7)))
	{
		const size_t y(targetPiece->getColor() == white ? 0 : 7);

		const auto& color{ targetPiece->getColor() };

		board.removePieceAt({ y, toX });

		std::cout << "PROMOTION !\n"
			<< "- 'Q' : Queen\n"
			<< "- 'B' : Bishop\n"
			<< "- 'N' : Knight\n"
			<< "- 'R' : Rook\n"
			<< "Select a piece: ";

		while (true)
		{
			char selection{};
			std::string_view pieceName{};
			std::cin >> selection;

			switch (selection)
			{
			case 'Q':
				m_board[y][toX].setPiece(PieceFactory::createQueen(color));
				pieceName = "queen";
				break;
			case 'B':
				m_board[y][toX].setPiece(PieceFactory::createBishop(color));
				pieceName = "bishop";
				break;
			case 'N':
				m_board[y][toX].setPiece(PieceFactory::createKnight(color));
				pieceName = "knight";
				break;
			case 'R':
				m_board[y][toX].setPiece(PieceFactory::createRook(color));
				pieceName = "rook";
				break;
			default:
				std::cout << "Wrong input. Try again: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			std::cout << "You selected a " << pieceName << ".\n\n";
			return;
		}
	}

	/* If the moved piece is a King or a Rook, set bool hasMoved to TRUE to prevent castling on a specific side if one of the rook has moved
	or to prevent castling completely if the king has moved */
	else if (targetPiece->getType() == rook || targetPiece->getType() == king)
	{
		switch (targetPiece->getType())
		{
		case rook:
		{
			auto* const rook{ dynamic_cast<Rook*>(targetPiece) }; // Casting to get the methode setHasMoved() that belongs only to Rook and King classes
			if (rook && !rook->getHasMoved())
				rook->setHasMoved(true);
			break;
		}
		case king:
		{
			auto* const king{ dynamic_cast<King*>(targetPiece) }; // Casting to get the methode setHasMoved() that belongs only to Rook and King classes
			if (king && !king->getHasMoved())
				king->setHasMoved(true);
			break;
		}
		default:
			throw std::runtime_error{ "Unexpected Type" };
		}
	}
}

void MoveExecutor::executeCastling(Board& board, Color playerColor, CastlingSide side)
{
	const size_t y(playerColor == white ? 7 : 0);
	constexpr size_t kingX{ 4 };
	constexpr size_t leftRookX{ 0 };
	constexpr size_t rightRookX{ 7 };

	auto& king{ m_board[y][kingX].getCase() };
	auto& leftRook{ m_board[y][leftRookX].getCase() };
	auto& rightRook{ m_board[y][rightRookX].getCase() };

	if (side == CastlingSide::left) // Castling queen side
	{
		m_board[y][2].getCase() = std::move(king);
		m_board[y][3].getCase() = std::move(leftRook);
		return { y, 3 }; // returning Rook coords to verify Check condition on opponent
	}

	else if (side == CastlingSide::right) // Castling right side
	{
		m_board[y][6].getCase() = std::move(king);
		m_board[y][5].getCase() = std::move(rightRook);
		return { y, 5 }; // returning Rook coords to verify Check condition on opponent
	}

	throw std::runtime_error{ "Bad Castling" };
}

void MoveExecutor::executePawnPromotion(Board& board, Position pawnPos, Type promotionType)
{
	if (targetCase.getPiece().getType() == pawn && ((targetCase.getPiece().getColor() == white && targetPositionY == 0) || (targetCase.getPiece().getColor() == black && targetPositionY == 7)))
	{
		const size_t y(targetCase.getPiece().getColor() == white ? 0 : 7);

		const auto& color{ m_board[y][targetPositionX].getPiece().getColor() };

		m_board[y][targetPositionX].getCase().reset();

		std::cout << "PROMOTION !\n"
			<< "- 'Q' : Queen\n"
			<< "- 'B' : Bishop\n"
			<< "- 'N' : Knight\n"
			<< "- 'R' : Rook\n"
			<< "Select a piece: ";

		while (true)
		{
			char selection{};
			std::string_view pieceName{};
			std::cin >> selection;

			switch (selection)
			{
			case 'Q':
				m_board[y][targetPositionX].setPiece(PieceFactory::createQueen(color));
				pieceName = "queen";
				break;
			case 'B':
				m_board[y][targetPositionX].setPiece(PieceFactory::createBishop(color));
				pieceName = "bishop";
				break;
			case 'N':
				m_board[y][targetPositionX].setPiece(PieceFactory::createKnight(color));
				pieceName = "knight";
				break;
			case 'R':
				m_board[y][targetPositionX].setPiece(PieceFactory::createRook(color));
				pieceName = "rook";
				break;
			default:
				std::cout << "Wrong input. Try again: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			std::cout << "You selected a " << pieceName << ".\n\n";
			return;
		}
	}
}