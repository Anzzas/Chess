#ifndef USERINPUT_H
#define USERINPUT_H
#include "board.h"

inline bool g_isCastling{};

std::pair<size_t, size_t> inputInitialCase(Board& board, const Piece::Color playerColor);

std::pair<size_t, size_t> inputTargetCase(const Board& board, const Piece::Color playerColor);

#endif