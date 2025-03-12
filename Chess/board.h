#ifndef BOARD_H
#define BOARD_H
#include "boardState.h"
#include "case.h"
#include "pieceFactory.h"
#include <array>
#include <algorithm>
#include <vector>
#include <optional>

using Point2D = std::array<std::array<Case, boardSettings::boardSize>, boardSettings::boardSize>;

class Board : public BoardState
{
public:

	Board()
	{
		// Setting up Black side pieces
		m_board[0][0].setPiece(PieceFactory::createRook(black));
		m_board[0][1].setPiece(PieceFactory::createKnight(black));
		m_board[0][2].setPiece(PieceFactory::createBishop(black));
		m_board[0][3].setPiece(PieceFactory::createQueen(black));
		m_board[0][4].setPiece(PieceFactory::createKing(black));
		m_board[0][5].setPiece(PieceFactory::createBishop(black));
		m_board[0][6].setPiece(PieceFactory::createKnight(black));
		m_board[0][7].setPiece(PieceFactory::createRook(black));

		// Setting up White side pieces
		m_board[7][0].setPiece(PieceFactory::createRook(white));
		m_board[7][1].setPiece(PieceFactory::createKnight(white));
		m_board[7][2].setPiece(PieceFactory::createBishop(white));
		m_board[7][3].setPiece(PieceFactory::createQueen(white));
		m_board[7][4].setPiece(PieceFactory::createKing(white));
		m_board[7][5].setPiece(PieceFactory::createBishop(white));
		m_board[7][6].setPiece(PieceFactory::createKnight(white));
		m_board[7][7].setPiece(PieceFactory::createRook(white));

		// Setting up pawns for Black and White
		for (size_t y{}; y < boardSettings::boardSize; y++)
		{
			for (size_t x{}; x < boardSettings::boardSize; x++)
			{
				if (y == 1)
					m_board[y][x].setPiece(PieceFactory::createPawn(black));
				if (y == 6)
					m_board[y][x].setPiece(PieceFactory::createPawn(white));
			}
		}
	}

	const Point2D& getBoard() const;
	friend std::ostream& operator<< (std::ostream& out, const Board& board);
	void movePiece(const Position startPosition, const Position targetPosition);
	const Position castle(const Color color, std::string_view castlingSide);
	std::optional<Position> getAttackingPieceCoord(Color attackingPieceColor) const;
	std::vector<Position> findAttackPath(Position attackerPos, Position kingPos) const;
	bool isCheckMate(Color kingColor);
	bool isSelfCheck(const Position startCase, const Position targetCase, const Color playerTurn);
	bool canCastleLeft(const Color playerTurn) const;
	bool canCastleRight(const Color playerTurn) const;
	bool isKingInCheck(const Color kingColor, const std::optional<Position> simulatePosition = std::nullopt) const;


	bool isEmpty(Position pos) const override;
	const Piece* getPieceAt(Position pos) const override;
	bool isPositionUnderAttack(Position pos, Color attackerColor) const override;
	const Position& getKingPosition(Color color) const override;
private:

	Point2D m_board{};
};

#endif