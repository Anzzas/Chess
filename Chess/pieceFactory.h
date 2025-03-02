#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H
#include "pawn.h" 
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include <memory>

class PieceFactory
{
public:

	PieceFactory() = delete;

	static std::unique_ptr<Piece> createPiece(Piece::Type type, Piece::Color color);

	static std::unique_ptr<Piece> createPawn(Piece::Color);
	static std::unique_ptr<Piece> createBishop(Piece::Color);
	static std::unique_ptr<Piece> createKnight(Piece::Color);
	static std::unique_ptr<Piece> createRook(Piece::Color);
	static std::unique_ptr<Piece> createQueen(Piece::Color);
	static std::unique_ptr<Piece> createKing(Piece::Color);

};

#endif