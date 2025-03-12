#include "pieceFactory.h"

std::unique_ptr<Piece> PieceFactory::createPawn(Color color)
{
	return std::make_unique<Pawn>(Pawn{ 'P', color, Type::pawn });
}

std::unique_ptr<Piece> PieceFactory::createBishop(Color color)
{
	return std::make_unique<Bishop>(Bishop{ 'B', color, Type::bishop });
}

std::unique_ptr<Piece> PieceFactory::createKnight(Color color)
{
	return std::make_unique<Knight>(Knight{ 'N', color, Type::knight });
}

std::unique_ptr<Piece> PieceFactory::createRook(Color color)
{
	return std::make_unique<Rook>(Rook{ 'R', color, Type::rook });
}

std::unique_ptr<Piece> PieceFactory::createQueen(Color color)
{
	return std::make_unique<Queen>(Queen{ 'Q', color, Type::queen });
}

std::unique_ptr<Piece> PieceFactory::createKing(Color color)
{
	return std::make_unique<King>(King{ 'K', color, Type::king });
}

std::unique_ptr<Piece> PieceFactory::createPiece(Type type, Color color)
{
	switch (type)
	{
	case pawn: return PieceFactory::createPawn(color);
	case bishop: return PieceFactory::createBishop(color);
	case knight: return PieceFactory::createKnight(color);
	case rook: return PieceFactory::createRook(color);
	case queen: return PieceFactory::createQueen(color);
	case king: return PieceFactory::createKing(color);
	default: throw std::runtime_error{ "Undefined Piece Type" };
	}
}