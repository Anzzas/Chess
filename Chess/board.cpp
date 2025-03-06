#include "board.h"

std::ostream& operator<< (std::ostream& out, const Board& board)
{
	int rowNumber{ 8 };
	for (size_t y{ 0 }; y < boardSettings::boardSize; y++)
	{
		out << rowNumber-- << "    ";
		for (size_t x{ 0 }; x < boardSettings::boardSize; x++)
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
	Case& startCase{ m_board[startPosition.first][startPosition.second] };
	Case& targetCase{ m_board[targetPosition.first][targetPosition.second] };

	targetCase.getCase() = std::move(startCase.getCase());

	if (targetCase.getPiece().getType() == Piece::pawn && ((targetCase.getPiece().getColor() == Piece::white && targetPosition.first == 0) || (targetCase.getPiece().getColor() == Piece::black && targetPosition.first == 7)))
	{
		size_t y{ static_cast<size_t>(targetCase.getPiece().getColor() == Piece::white ? 0 : 7) };

		Piece::Color color{ m_board[y][targetPosition.second].getPiece().getColor() };

		m_board[y][targetPosition.second].getCase().reset();

		std::cout << "PROMOTION !\n"
			<< "- 'Q' : Queen\n"
			<< "- 'B' : Bishop\n"
			<< "- 'N' : Knight\n"
			<< "- 'R' : Rook\n"
			<< "Select a piece: ";

		while (true)
		{
			char selection{};
			std::cin >> selection;

			switch (selection)
			{
			case 'Q':
				m_board[y][targetPosition.second].setPiece(PieceFactory::createQueen(color));
				break;
			case 'B':
				m_board[y][targetPosition.second].setPiece(PieceFactory::createBishop(color));
				break;
			case 'N':
				m_board[y][targetPosition.second].setPiece(PieceFactory::createKnight(color));
				break;
			case 'R':
				m_board[y][targetPosition.second].setPiece(PieceFactory::createRook(color));
				break;
			default:
				std::cout << "Wrong input. Try again: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			std::cout << "You selected a " << selection << ".\n\n";
			return;
		}
	}

	else if (targetCase.getPiece().getType() == Piece::rook || targetCase.getPiece().getType() == Piece::king)
	{
		Piece* piece{ targetCase.getCase().get() };

		switch (targetCase.getPiece().getType())
		{
		case Piece::rook:
		{
			auto* rook{ dynamic_cast<Rook*>(piece) };
			if (rook)
				rook->setHasMoved(true);
			break;
		}
		case Piece::king:
		{
			auto* king{ dynamic_cast<King*>(piece) };
			if (king)
				king->setHasMoved(true);
			break;
		}
		default:
			throw std::runtime_error{ "Unexpected Type" };
		}

	}
}

bool Board::isKingInCheck(Piece::Color kingColor, std::pair<size_t, size_t> simulatePosition) const
{
	std::pair<size_t, size_t> kingPosition{};

	// If a value is specified in arguments then checks for a specified position instead
	if (simulatePosition.first < boardSettings::boardSize && simulatePosition.second < boardSettings::boardSize)
		kingPosition = simulatePosition;

	// Getting King's position
	else
		kingPosition = getKingPosition(kingColor);

	// Checks if any opponent piece can reach King's position
	for (size_t y{ 0 }; y < boardSettings::boardSize; y++)
	{
		for (size_t x{ 0 }; x < boardSettings::boardSize; x++)
		{
			if (!m_board[y][x].isEmpty() && m_board[y][x].getPiece().getColor() != kingColor)
			{
				std::pair<size_t, size_t> threatPosition{ y, x };

				if (dynamic_cast<Pawn*>(m_board[y][x].getCase().get())) // Simulate King for the special case where the pawn can move 2 cases forward
				{
					// Vérifier uniquement si le pion peut capturer à la position du roi
					int pawnDirection = (m_board[y][x].getPiece().getColor() == Piece::white) ? -1 : 1;

					// Un pion peut capturer uniquement en diagonale
					if ((y + pawnDirection == kingPosition.first) && (x + 1 == kingPosition.second || x - 1 == kingPosition.second)) 
						return true;
				}

				else if (!dynamic_cast<King*>(m_board[y][x].getCase().get()))
				{
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
	for (size_t y{ 0 }; y < boardSettings::boardSize; y++)
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
	std::pair<size_t, size_t> kingPosition{ getKingPosition(kingColor) };
	size_t x_king{ kingPosition.second };
	size_t y_king{ kingPosition.first };

	if (!isKingInCheck(kingColor))
		return false;

	// 1. Vérifier si le roi peut s'échapper en se déplaçant
	// Up, down, left, right, diagonals check
	for (int dy = -1; dy <= 1; dy++) 
{
		for (int dx = -1; dx <= 1; dx++) 
		{
			// Ignorer la position actuelle du roi
			if (dx == 0 && dy == 0)
				continue;

			// Calculer la nouvelle position potentielle
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
	std::pair<size_t, size_t> attackingPieceCoord(getAttackingPieceCoord(kingColor == Piece::white ? Piece::black : Piece::white));
	const Case& attackingPieceCase{ m_board[attackingPieceCoord.first][attackingPieceCoord.second] };

	for (size_t y{}; y < boardSettings::boardSize; y++)
	{
		for (size_t x{}; x < boardSettings::boardSize; x++)
		{
			if (!m_board[y][x].isEmpty() && m_board[y][x].getPiece().getColor() == kingColor)
			{
				// If a piece of the same color as king can take the attacking piece, then it is not checkmate
				if (m_board[y][x].getPiece().canMoveTo(*this, std::pair{ y, x }, attackingPieceCoord))
					return false;

				// 3. Vérifie si une pièce peut se déplacer dans les cases de findAttackPath
				std::vector<std::pair<size_t, size_t>> path = findAttackPath(attackingPieceCoord, kingPosition);
				for (auto& e : path)
				{
					if (m_board[y][x].getPiece().canMoveTo(*this, std::pair{ y, x }, std::pair{e.first, e.second}))
						return false;
				}
			}
		}
	}

	return true;
}

std::pair<size_t, size_t> Board::getAttackingPieceCoord(Piece::Color attackingPieceColor) const
{
	std::pair<size_t, size_t> kingPosition{ getKingPosition(attackingPieceColor == Piece::white ? Piece::black : Piece::white) };

	for (size_t y{ 0 }; y < boardSettings::boardSize; y++)
	{
		for (size_t x{ 0 }; x < boardSettings::boardSize; x++)
		{
			// Vérifie si la case contient une pièce de couleur opposée
			if (!m_board[y][x].isEmpty() && m_board[y][x].getPiece().getColor() == attackingPieceColor)
			{
				std::pair<size_t, size_t> threatPosition{ y, x };
				Piece* piece = m_board[y][x].getCase().get();

				// Traitement spécial pour les pions (qui ont des règles spéciales de capture)
				if (dynamic_cast<Pawn*>(piece))
				{
					// Détermine la direction du pion selon sa couleur
					int pawnDirection = (piece->getColor() == Piece::white) ? -1 : 1;

					// Vérifie si le pion peut capturer le roi (diagonale avant uniquement)
					if ((y + pawnDirection == kingPosition.first) && (abs(static_cast<int>(x) - static_cast<int>(kingPosition.second)) == 1))
						return { y, x };
				}
				// Pour toutes les pièces sauf les rois
				else if (piece && piece->getType() != Piece::king)
				{
					// Utilise la méthode générique de vérification de mouvement
					if (piece->canMoveTo(*this, threatPosition, kingPosition))
						return { y, x };
				}
			}
		}
	}

	// Aucune pièce n'attaque le roi - retourne une position invalide comme marqueur
	return { boardSettings::boardSize, boardSettings::boardSize };
}

std::vector<std::pair<size_t, size_t>> Board::findAttackPath(std::pair<size_t, size_t> attackerPos, std::pair<size_t, size_t> kingPos) const
{
	std::vector<std::pair<size_t, size_t>> path;

	// Calculer la direction de l'attaque
	const int attacker_Y{ static_cast<int>(attackerPos.first) };
	const int attacker_X{ static_cast<int>(attackerPos.second) };

	const int king_Y{ static_cast<int>(kingPos.first) };
	const int king_X{ static_cast<int>(kingPos.second) };

	const int deltaY{ king_Y - attacker_Y };
	const int deltaX{ king_X - attacker_X };

	const int dirY{ (deltaY == 0) ? 0 : (deltaY > 0 ? 1 : -1) };
	const int dirX{ (deltaX == 0) ? 0 : (deltaX > 0 ? 1 : -1) };

	int currentY{ attacker_Y + dirY };
	int currentX{ attacker_X + dirX };

	// Collecter toutes les cases sur cette ligne/diagonale
	while (currentY != king_Y || currentX != king_X)
	{
		if (currentY >= 0 && currentY < boardSettings::boardSize && currentX >= 0 && currentX < boardSettings::boardSize)
			path.push_back({ static_cast<size_t>(currentY), static_cast<size_t>(currentX) });

		currentY += dirY;
		currentX += dirX;
	}
	return path;
}

bool Board::isSelfCheck(std::pair<size_t, size_t> startCase, std::pair<size_t, size_t> targetCase, Piece::Color playerTurn)
{

	// Simulating move to verify is the player don't put himself in check

	// Getting a copy of the starting case before moving them and later verifying if targetCase was not empty to get also a copy
	std::unique_ptr<Piece> tempStartCase{ PieceFactory::createPiece(m_board[startCase.first][startCase.second].getPiece().getType(), m_board[startCase.first][startCase.second].getPiece().getColor()) };
	std::unique_ptr<Piece> tempTargetCase{};

	movePiece(startCase, targetCase); // Move the piece normally

	if (!isKingInCheck(playerTurn)) // If player own king is not self checked then everything is OK
		return false;

	if (!m_board[targetCase.first][targetCase.second].isEmpty()) // If the targetCase is not empty then create a copy of it to restore it later
		tempTargetCase = PieceFactory::createPiece(m_board[targetCase.first][targetCase.second].getPiece().getType(), m_board[targetCase.first][targetCase.second].getPiece().getColor());

	// Put back the moved piece from targetCase to startCase
	m_board[startCase.first][startCase.second].getCase() = std::move(tempStartCase);

	if (tempTargetCase) // if targetCase was not empty, then restoring the previous piece. Else leave it empty
		m_board[targetCase.first][targetCase.second].getCase() = std::move(tempTargetCase);

	return true; // If that move put the player himself in check, restore last position and make the player try again

}

bool Board::canCastleLeft(Piece::Color playerTurn) const
{
	const size_t y{ static_cast<size_t>(playerTurn == Piece::white ? 7 : 0) };
	constexpr size_t kingX{ 4 };
	constexpr size_t leftRookX{ 0 };
	constexpr size_t rightRookX{ 7 };

	auto* king{ dynamic_cast<King*>(m_board[y][kingX].getCase().get()) };

	if (!king || king->getHasMoved())
		return false;

		// Left side check
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
			auto* leftRook{ dynamic_cast<Rook*>(m_board[y][leftRookX].getCase().get()) };

			if (leftRook && !leftRook->getHasMoved())
				return true;
		}
	return false;
}

bool Board::canCastleRight(Piece::Color playerTurn) const
{
	const size_t y{ static_cast<size_t>(playerTurn == Piece::white ? 7 : 0) };
	constexpr size_t kingX{ 4 };
	constexpr size_t leftRookX{ 0 };
	constexpr size_t rightRookX{ 7 };

	auto* king{ dynamic_cast<King*>(m_board[y][kingX].getCase().get()) };

	if (!king || king->getHasMoved())
		return false;

	// Right side check
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
		auto* rightRook{ dynamic_cast<Rook*>(m_board[y][rightRookX].getCase().get()) };

		if (rightRook && !rightRook->getHasMoved())
			return true;
	}
	return false;
}

void Board::castle(Piece::Color color, std::string_view castlingSide)
{
	const size_t y{ static_cast<size_t>(color == Piece::white ? 7 : 0) };
	constexpr size_t kingX{ 4 };
	constexpr size_t leftRookX{ 0 };
	constexpr size_t rightRookX{ 7 };

	std::unique_ptr<Piece>& king{ m_board[y][kingX].getCase() };
	std::unique_ptr<Piece>& leftRook{ m_board[y][leftRookX].getCase() };
	std::unique_ptr<Piece>& rightRook{ m_board[y][rightRookX].getCase() };

	if (castlingSide == "oq") // Castling queen side
	{
		m_board[y][2].getCase() = std::move(king);
		m_board[y][3].getCase() = std::move(leftRook);
	}

	else if (castlingSide == "oo") // Castling right side
	{
		m_board[y][6].getCase() = std::move(king);
		m_board[y][5].getCase() = std::move(rightRook);
	}
}
