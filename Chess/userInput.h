#ifndef USERINPUT_H
#define USERINPUT_H
#include "position.h"
#include "board.h"

inline bool g_isCastling{};

Position inputInitialCase(Board& board, const Color playerColor);

std::optional<Position> inputTargetCase(BoardState& board, const Position startCase, const Color playerColor);

#endif