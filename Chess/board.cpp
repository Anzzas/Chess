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

	targetCase.replacePiece(startCase.getCase());
}

bool Board::isKingInCheck(Piece::Color kingColor) const 
{
	// 1. Trouver la position du roi de la couleur spécifiée
	std::pair<size_t, size_t> kingPosition{};

	bool kingFound{};
	for (size_t x{ 0 }; x < boardSettings::boardSize; x++)
	{
		auto found{ std::find_if(m_board[x].begin(), m_board[x].end(), [&](const Case& c)
			{
			return c.getPiece().getType() == Piece::king && c.getPiece().getColor() == kingColor;
			}) };

		if (found == m_board[x].end())
			throw std::runtime_error{ "No king found" };

		else
		{
			size_t y{ std::distance(m_board[x].begin(), found)};
			kingPosition = { y, x };
			kingFound = true;
			break;
		}
	}
	// 2. Vérifier si une pièce adverse peut atteindre cette position
}