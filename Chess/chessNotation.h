#ifndef CHESSNOTATION_H
#define CHESSNOTATION_H
#include "position.h"
#include "userInterface.h"

class ChessNotation
{
public:

	static Position fromAlgebraic(const std::string& notation);
	static std::string toAlgebraic(Position pos);
};

#endif