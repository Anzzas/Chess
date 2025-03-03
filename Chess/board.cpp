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

bool Board::isKingInCheck(Piece::Color kingColor, std::pair<size_t, size_t> simulatePosition) const
{
	std::pair<size_t, size_t> kingPosition{};

	// If a value is specified in arguments then checks for a specified position instead
	if (simulatePosition.first < boardSettings::boardSize && simulatePosition.second < boardSettings::boardSize)
		std::pair<size_t, size_t> kingPosition = simulatePosition;

	// Getting King's position
	else
		std::pair<size_t, size_t> kingPosition = getKingPosition(kingColor);

	// Checks if any opponent piece can reach King's position
	for (size_t y{ 0 }; y < boardSettings::boardSize; y++)
	{
		for (size_t x{ 0 }; x < boardSettings::boardSize; x++)
		{
			if (!m_board[y][x].isEmpty() && m_board[y][x].getPiece().getColor() != kingColor)
			{
				std::pair<size_t, size_t> threatPosition{ y, x };

				if (m_board[y][x].getPiece().canMoveTo(*this, threatPosition, kingPosition))
					return true;
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

}