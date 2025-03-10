#include "board.h"

std::ostream& operator<< (std::ostream& out, const Board& board)
{
	int rowNumber{ boardSettings::boardSize };
	for (size_t y{}; y < boardSettings::boardSize; y++)
	{
		out << rowNumber-- << "    ";
		for (size_t x{}; x < boardSettings::boardSize; x++)
		{
			out << board.m_board[y][x] << " ";
		}
		out << "\n";
	}

	out << "\n     ";
	char colLetter{ 97 };
	for (size_t count{}; count < boardSettings::boardSize; count++)
	{
		out << colLetter++ << " ";
	}
	return out;
}

const Point2D& Board::getBoard() const
{
	return m_board;
}

void Board::movePiece(const std::pair<size_t, size_t> startPosition, const std::pair<size_t, size_t> targetPosition)
{
	const auto [targetPositionY, targetPositionX] = targetPosition;
	Case& targetCase{ m_board[targetPositionY][targetPositionX] };
	Case& startCase{ m_board[startPosition.first][startPosition.second] };

	targetCase.getCase() = std::move(startCase.getCase());

	// Promotion check. If the moved piece is of type Pawn and on Y = 0 (for WHITE) OR Y = 7 (for BLACK), then allow promotion
	if (targetCase.getPiece().getType() == Piece::pawn && ((targetCase.getPiece().getColor() == Piece::white && targetPositionY == 0) || (targetCase.getPiece().getColor() == Piece::black && targetPositionY == 7)))
	{
		const size_t y(targetCase.getPiece().getColor() == Piece::white ? 0 : 7);

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

	/* If the moved piece is a King or a Rook, set bool hasMoved to TRUE to prevent castling on a specific side if one of the rook has moved
	or to prevent castling completely if the king has moved */
	else if (targetCase.getPiece().getType() == Piece::rook || targetCase.getPiece().getType() == Piece::king)
	{
		Piece* piece{ targetCase.getCase().get() };

		switch (targetCase.getPiece().getType())
		{
		case Piece::rook:
		{
			auto* const rook{ dynamic_cast<Rook*>(piece) }; // Casting to get the methode setHasMoved() that belongs only to Rook and King classes
			if (rook && !rook->getHasMoved())
				rook->setHasMoved(true);
			break;
		}
		case Piece::king:
		{
			auto* const king{ dynamic_cast<King*>(piece) }; // Casting to get the methode setHasMoved() that belongs only to Rook and King classes
			if (king && !king->getHasMoved())
				king->setHasMoved(true);
			break;
		}
		default:
			throw std::runtime_error{ "Unexpected Type" };
		}
	}
}

bool Board::isKingInCheck(const Piece::Color kingColor, const std::optional<std::pair<size_t, size_t>> simulatePosition) const
{
	// If a value is specified in arguments then checks for a specified position instead (to simulate a move)
	// Else, Getting normal King's position
	const auto kingPosition{ simulatePosition ? *simulatePosition : getKingPosition(kingColor)};
	const auto [kingY, kingX] = kingPosition;

	// Checks if any opponent piece can reach King's position
	for (size_t y{}; y < boardSettings::boardSize; y++)
	{
		for (size_t x{}; x < boardSettings::boardSize; x++)
		{
			if (!m_board[y][x].isEmpty() && m_board[y][x].getPiece().getColor() != kingColor)
			{
				// Checking special case for Pawn behavior
				if (m_board[y][x].getPiece().getType() == Piece::pawn) // Simulate King for the special case where the pawn can move 2 cases forward
				{
					// Checks only if the Pawn is attacking the king's position
					int pawnDirection = (m_board[y][x].getPiece().getColor() == Piece::white) ? -1 : 1;

					// Pawn can only attack on forward diagonals
					if ((static_cast<int>(y) + pawnDirection == static_cast<int>(kingY)) && (x + 1 == kingX || static_cast<int>(x) - 1 == static_cast<int>(kingX))) 
						return true;
				}

				// For any other pieces except King
				else if (m_board[y][x].getPiece().getType() != Piece::king)
				{
					std::pair threatPosition{ y, x };
					if (m_board[y][x].getPiece().canMoveTo(*this, threatPosition, kingPosition))
						return true;
				}
			}
		}
	}
	return false;
}

const std::pair<size_t, size_t> Board::getKingPosition(Piece::Color kingColor) const
{
	bool kingFound{};
	for (size_t y{}; y < boardSettings::boardSize; y++)
	{
		auto found{ std::find_if(m_board[y].begin(), m_board[y].end(), [&](const Case& c)
			{
				if (c.isEmpty())
					return false;

			return c.getPiece().getType() == Piece::king && c.getPiece().getColor() == kingColor;
			}) };

		if (found != m_board[y].end())
		{
			size_t x{ static_cast<size_t>(std::distance(m_board[y].begin(), found)) };
			return { y, x };
		}
	}

	if (!kingFound)
		throw std::runtime_error{ "No king found" };

	return { boardSettings::boardSize, boardSettings::boardSize }; // error value
}

bool Board::isCheckMate(Piece::Color kingColor)
{
	const auto kingPosition{ getKingPosition(kingColor) };
	const auto [y_king, x_king] = kingPosition;

	if (!isKingInCheck(kingColor))
		return false;

	// 1. Verifying if the king can move to escape the attack
	// Up, down, left, right, diagonals check
	for (int dy = -1; dy <= 1; dy++) 
{
		for (int dx = -1; dx <= 1; dx++) 
		{
			// Ignore actual King's position
			if (dx == 0 && dy == 0)
				continue;

			// Calculate potential new position
			int newY = static_cast<int>(y_king) + dy;
			int newX = static_cast<int>(x_king) + dx;

			// Vérifier les limites de l'échiquier
			if (newY >= 0 && newY < boardSettings::boardSize && newX >= 0 && newX < boardSettings::boardSize) 
			{
				// Vérifier si le roi peut se déplacer à cette position
				if (m_board[y_king][x_king].getPiece().canMoveTo(*this, kingPosition, std::pair<size_t, size_t>{static_cast<size_t>(newY), static_cast<size_t>(newX)}))
					return false;  // Le roi peut s'échapper
			}
		}
	}

	// 2. Verifying if kingColor pieces can take the attacker out
	const auto attackingPieceCoord(getAttackingPieceCoord(kingColor == Piece::white ? Piece::black : Piece::white));
	
	if (!attackingPieceCoord)
		return false;

	for (size_t y{}; y < boardSettings::boardSize; y++)
	{
		for (size_t x{}; x < boardSettings::boardSize; x++)
		{
			if (!m_board[y][x].isEmpty() && m_board[y][x].getPiece().getColor() == kingColor)
			{
				// 3. If a piece of the same color as king can take the attacking piece, then it is not checkmate
				if (m_board[y][x].getPiece().canMoveTo(*this, { y, x }, *attackingPieceCoord))
					return false;

				// 4. Verifying if an ally piece can move to one of the cases of the attack path to block the attack
				const auto path = findAttackPath(*attackingPieceCoord, kingPosition);
				for (const auto&[attackedCaseY, attackedCaseX] : path)
				{
					if (m_board[y][x].getPiece().canMoveTo(*this, { y, x }, {attackedCaseY, attackedCaseX}))
						return false;
				}
			}
		}
	}
	return true;
}

std::optional<std::pair<size_t, size_t>> Board::getAttackingPieceCoord(Piece::Color attackingPieceColor) const
{
	const auto kingPosition{ getKingPosition(attackingPieceColor == Piece::white ? Piece::black : Piece::white) };
	const auto [KingY, KingX] = kingPosition;

	for (size_t y{ 0 }; y < boardSettings::boardSize; y++)
	{
		for (size_t x{ 0 }; x < boardSettings::boardSize; x++)
		{
			// Verifying is the case is not empty and containing opposing color
			if (!m_board[y][x].isEmpty() && m_board[y][x].getPiece().getColor() == attackingPieceColor)
			{
				const Piece* const piece{ m_board[y][x].getCase().get() };

				// Special case for Pawns 
				if (piece->getType() == Piece::pawn)
				{
					// Détermine la direction du pion selon sa couleur
					int pawnDirection = (piece->getColor() == Piece::white) ? -1 : 1;

					// Vérifie si le pion peut capturer le roi (diagonale avant uniquement)
					if ((y + pawnDirection == KingY) && (abs(static_cast<int>(x) - static_cast<int>(KingX)) == 1))
						return std::pair{ y, x };
				}
				// For all pieces except the King
				else if (piece && piece->getType() != Piece::king)
				{
					const std::pair threatPosition{ y, x };
					// Using generic method of movement verification
					if (piece->canMoveTo(*this, threatPosition, kingPosition))
						return std::pair{ y, x };
				}
			}
		}
	}
	// The king isn't under attack, returning nullopt
	return {};
}

std::vector<std::pair<size_t, size_t>> Board::findAttackPath(std::pair<size_t, size_t> attackerPos, std::pair<size_t, size_t> kingPos) const
{
	std::vector<std::pair<size_t, size_t>> path;

	const auto [attacker_Y, attacker_X] = attackerPos;
	const auto [king_Y, king_X] = kingPos;


	// Calculating direction
	const int deltaY{ static_cast<int>(king_Y) - static_cast<int>(attacker_Y) };
	const int deltaX{ static_cast<int>(king_X) - static_cast<int>(attacker_X) };

	const int dirY{ (deltaY == 0) ? 0 : (deltaY > 0 ? 1 : -1) };
	const int dirX{ (deltaX == 0) ? 0 : (deltaX > 0 ? 1 : -1) };

	int currentY{ static_cast<int>(attacker_Y) + dirY };
	int currentX{ static_cast<int>(attacker_X) + dirX };

	// Collecter toutes les cases sur cette ligne/diagonale
	while (currentY != static_cast<int>(king_Y) || currentX != static_cast<int>(king_X))
	{
		if (currentY >= 0 && currentY < boardSettings::boardSize && currentX >= 0 && currentX < boardSettings::boardSize)
			path.push_back({ static_cast<size_t>(currentY), static_cast<size_t>(currentX) });

		currentY += dirY;
		currentX += dirX;
	}
	return path;
}

bool Board::isSelfCheck(const std::pair<size_t, size_t> startCase, const std::pair<size_t, size_t> targetCase, const Piece::Color playerTurn)
{
	const auto [startCaseY, startCaseX] = startCase;
	const auto [targetCaseY, targetCaseX] = targetCase;

	// Simulating move to verify is the player don't put himself in check
	// Getting a copy of the starting case before moving them and later verifying if targetCase was not empty to get also a copy
	auto tempStartCase{ PieceFactory::createPiece(m_board[startCaseY][startCaseX].getPiece().getType(), m_board[startCaseY][startCaseX].getPiece().getColor()) };
	std::unique_ptr<Piece> tempTargetCase{};

	// If the targetCase is not empty then create a copy of it to restore it later
	if(!m_board[targetCaseY][targetCaseX].isEmpty())
	tempTargetCase = PieceFactory::createPiece(m_board[targetCaseY][targetCaseX].getPiece().getType(), m_board[targetCaseY][targetCaseX].getPiece().getColor());


	movePiece(startCase, targetCase); // Move the piece normally

	if (!isKingInCheck(playerTurn)) // If player own king is not self checked after the move, then everything is OK
	{
		// Putting back the pieces to their original cases
		m_board[startCaseY][startCaseX].getCase() = std::move(tempStartCase);
		m_board[targetCaseY][targetCaseX].getCase() = std::move(tempTargetCase);
		return false;
	}

	// Else, the king after the move is in fact in check
	// Putting back the moved piece to their original cases
	m_board[startCaseY][startCaseX].getCase() = std::move(tempStartCase);
	m_board[targetCaseY][targetCaseX].getCase() = std::move(tempTargetCase);

	return true; // If that move put the player himself in check, make the player try again
}

bool Board::canCastleLeft(const Piece::Color playerTurn) const
{
	const size_t y(playerTurn == Piece::white ? 7 : 0);
	constexpr size_t kingX{ 4 };
	constexpr size_t leftRookX{ 0 };
	constexpr size_t rightRookX{ 7 };

	const auto* const king{ dynamic_cast<King*>(m_board[y][kingX].getCase().get()) };

	if (!king || king->getHasMoved())
		return false;

		// Left side check if cases between left Rook and King are empty
		// and if these cases are under attack by opponent pieces
		if (m_board[y][1].isEmpty() && m_board[y][2].isEmpty() && m_board[y][3].isEmpty())
		{
			for (size_t attackerY{}; attackerY < boardSettings::boardSize; attackerY++)
			{
				for (size_t attackerX{}; attackerX < boardSettings::boardSize; attackerX++)
				{
					if (!m_board[attackerY][attackerX].isEmpty() && m_board[attackerY][attackerX].getPiece().getColor() != playerTurn)
					{
						for (size_t targetX{ 1 }; targetX < 4; targetX++)
						{
							if (m_board[attackerY][attackerX].getPiece().canMoveTo(*this, { attackerY, attackerX }, { y, targetX }))
								return false;
						}
					}
				}
			}

			assert(y < boardSettings::boardSize);
			const auto* const leftRook{ dynamic_cast<Rook*>(m_board[y][leftRookX].getCase().get()) };

			if (leftRook && !leftRook->getHasMoved())
				return true;
		}
	return false;
}

bool Board::canCastleRight(const Piece::Color playerTurn) const
{
	const size_t y(playerTurn == Piece::white ? 7 : 0);
	constexpr size_t kingX{ 4 };
	constexpr size_t leftRookX{ 0 };
	constexpr size_t rightRookX{ 7 };

	const auto* const king{ dynamic_cast<King*>(m_board[y][kingX].getCase().get()) };

	if (!king || king->getHasMoved())
		return false;

	// Right side check if cases between right Rook and King are empty
	// and if these cases are under attack by opponent pieces
	if (m_board[y][5].isEmpty() && m_board[y][6].isEmpty())
	{
		for (size_t attackerY{}; attackerY < boardSettings::boardSize; attackerY++)
		{
			for (size_t attackerX{}; attackerX < boardSettings::boardSize; attackerX++)
			{
				if (!m_board[attackerY][attackerX].isEmpty() && m_board[attackerY][attackerX].getPiece().getColor() != playerTurn)
				{
					for (size_t targetX{ 5 }; targetX < 7; targetX++)
					{
						if (m_board[attackerY][attackerX].getPiece().canMoveTo(*this, { attackerY, attackerX }, { y, targetX }))
							return false;
					}
				}
			}
		}

		assert(y < boardSettings::boardSize);
		const auto* const rightRook{ dynamic_cast<Rook*>(m_board[y][rightRookX].getCase().get()) };

		if (rightRook && !rightRook->getHasMoved())
			return true;
	}
	return false;
}

const std::pair<size_t, size_t> Board::castle(const Piece::Color color, std::string_view castlingSide)
{
	const size_t y(color == Piece::white ? 7 : 0);
	constexpr size_t kingX{ 4 };
	constexpr size_t leftRookX{ 0 };
	constexpr size_t rightRookX{ 7 };

	auto& king{ m_board[y][kingX].getCase() };
	auto& leftRook{ m_board[y][leftRookX].getCase() };
	auto& rightRook{ m_board[y][rightRookX].getCase() };

	if (castlingSide == "oq") // Castling queen side
	{
		m_board[y][2].getCase() = std::move(king);
		m_board[y][3].getCase() = std::move(leftRook);
		return { y, 3 }; // returning Rook coords to verify Check condition on opponent
	}

	else if (castlingSide == "oo") // Castling right side
	{
		m_board[y][6].getCase() = std::move(king);
		m_board[y][5].getCase() = std::move(rightRook);
		return { y, 5 }; // returning Rook coords to verify Check condition on opponent
	}

	throw std::runtime_error{ "Bad Castling" };
}
