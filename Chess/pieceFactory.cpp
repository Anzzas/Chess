#include "pieceFactory.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

std::unique_ptr<Piece> PieceFactory::createPawn(Piece::Color color)
{
	return std::make_unique<Pawn>(Pawn{ 'P', color, Piece::Type::pawn });
}

std::unique_ptr<Piece> PieceFactory::createBishop(Piece::Color color)
{
	return std::make_unique<Bishop>(Bishop{ 'B', color, Piece::Type::bishop });
}

std::unique_ptr<Piece> PieceFactory::createKnight(Piece::Color color)
{
	return std::make_unique<Knight>(Knight{ 'N', color, Piece::Type::knight });
}

std::unique_ptr<Piece> PieceFactory::createRook(Piece::Color color)
{
	return std::make_unique<Rook>(Rook{ 'R', color, Piece::Type::rook });
}

std::unique_ptr<Piece> PieceFactory::createQueen(Piece::Color color)
{
	return std::make_unique<Queen>(Queen{ 'Q', color, Piece::Type::queen });
}

std::unique_ptr<Piece> PieceFactory::createKing(Piece::Color color)
{
	return std::make_unique<King>(King{ 'K', color, Piece::Type::king });
}