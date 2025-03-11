#ifndef BOARD_H
#define BOARD_H
#include "boardState.h"
#include "position.h"
#include "case.h"
#include "pieceFactory.h"
#include <array>
#include <map>
#include <algorithm>
#include <vector>
#include <optional>

namespace boardSettings
{
	constexpr int boardSize{ 8 };

	inline std::map<std::string, std::pair<size_t, size_t>> choiceToCoord = []() 
		{
			std::map<std::string, std::pair<size_t, size_t>> result;
			std::string cols{ "abcdefgh" };

			for (size_t x{}; x < cols.size(); x++)
			{
				for (size_t y{}; y < cols.size(); y++)
				{
					std::string key{ cols[x] };
					key += std::to_string(y + 1);
					result.try_emplace(key, std::pair{ (boardSize - 1) - y, x });
				}
			}

			return result;

		}();
}

using Point2D = std::array<std::array<Case, boardSettings::boardSize>, boardSettings::boardSize>;

class Board : public BoardState
{
public:

	Board()
	{
		// Setting up Black side pieces
		m_board[0][0].setPiece(PieceFactory::createRook(Piece::black));
		m_board[0][1].setPiece(PieceFactory::createKnight(Piece::black));
		m_board[0][2].setPiece(PieceFactory::createBishop(Piece::black));
		m_board[0][3].setPiece(PieceFactory::createQueen(Piece::black));
		m_board[0][4].setPiece(PieceFactory::createKing(Piece::black));
		m_board[0][5].setPiece(PieceFactory::createBishop(Piece::black));
		m_board[0][6].setPiece(PieceFactory::createKnight(Piece::black));
		m_board[0][7].setPiece(PieceFactory::createRook(Piece::black));

		// Setting up White side pieces
		m_board[7][0].setPiece(PieceFactory::createRook(Piece::white));
		m_board[7][1].setPiece(PieceFactory::createKnight(Piece::white));
		m_board[7][2].setPiece(PieceFactory::createBishop(Piece::white));
		m_board[7][3].setPiece(PieceFactory::createQueen(Piece::white));
		m_board[7][4].setPiece(PieceFactory::createKing(Piece::white));
		m_board[7][5].setPiece(PieceFactory::createBishop(Piece::white));
		m_board[7][6].setPiece(PieceFactory::createKnight(Piece::white));
		m_board[7][7].setPiece(PieceFactory::createRook(Piece::white));

		// Setting up pawns for Black and White
		for (size_t y{}; y < boardSettings::boardSize; y++)
		{
			for (size_t x{}; x < boardSettings::boardSize; x++)
			{
				if (y == 1)
					m_board[y][x].setPiece(PieceFactory::createPawn(Piece::black));
				if (y == 6)
					m_board[y][x].setPiece(PieceFactory::createPawn(Piece::white));
			}
		}
	}

	const Point2D& getBoard() const;
	friend std::ostream& operator<< (std::ostream& out, const Board& board);
	void movePiece(const std::pair<size_t, size_t> startPosition, const std::pair<size_t, size_t> targetPosition);
	const std::pair<size_t, size_t> getKingPosition(Piece::Color kingColor) const;
	const std::pair<size_t, size_t> castle(const Piece::Color color, std::string_view castlingSide);
	std::optional<std::pair<size_t, size_t>> getAttackingPieceCoord(Piece::Color attackingPieceColor) const;
	std::vector<std::pair<size_t, size_t>> findAttackPath(std::pair<size_t, size_t> attackerPos, std::pair<size_t, size_t> kingPos) const;
	bool isCheckMate(Piece::Color kingColor);
	bool isSelfCheck(const std::pair<size_t, size_t> startCase, const std::pair<size_t, size_t> targetCase, const Piece::Color playerTurn);
	bool canCastleLeft(const Piece::Color playerTurn) const;
	bool canCastleRight(const Piece::Color playerTurn) const;
	bool isKingInCheck(const Piece::Color kingColor, const std::optional<std::pair<size_t, size_t>> simulatePosition = std::nullopt) const;

private:

	Point2D m_board{};
};

#endif