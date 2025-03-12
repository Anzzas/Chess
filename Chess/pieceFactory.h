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

	static std::unique_ptr<Piece> createPiece(Type type, Color color);

	static std::unique_ptr<Piece> createPawn(Color);
	static std::unique_ptr<Piece> createBishop(Color);
	static std::unique_ptr<Piece> createKnight(Color);
	static std::unique_ptr<Piece> createRook(Color);
	static std::unique_ptr<Piece> createQueen(Color);
	static std::unique_ptr<Piece> createKing(Color);

};

#endif