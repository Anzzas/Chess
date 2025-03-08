#include "king.h"
#include "board.h"

bool King::canMoveTo(const Board& board, const std::pair<size_t, size_t> startPosition, const std::pair<size_t, size_t> targetPosition) const
{
    // Starting case coordinates
    const auto [y_Start, x_Start] = startPosition;

    // Target case coordinates 
    const auto [y_Target, x_Target] = targetPosition;

    // Verifying the target case is on a valid case
    if (x_Target >= boardSettings::boardSize || y_Target >= boardSettings::boardSize) {
        return false;
    }

    // Verifying if the target case is empty or contains an ennemy piece
    const Case& TargetCase{ board.getBoard()[y_Target][x_Target] };
    if (!TargetCase.isEmpty() && TargetCase.getPiece().getColor() == m_color)
        return false;

    else if (!TargetCase.isEmpty() && TargetCase.getPiece().getColor() != m_color)
        return true;

    // Verifying the king doesn't put himself in Check
    if (!board.isKingInCheck(m_color, targetPosition))
    {
        // Verifying the move is one case for every direction
        if (std::abs(static_cast<int>(y_Target) - static_cast<int>(y_Start)) <= 1 &&
            std::abs(static_cast<int>(x_Target) - static_cast<int>(x_Start)) <= 1 &&
            (y_Target != y_Start || x_Target != x_Start)) 
            return true;
    }
    return false;
}

const bool& King::getHasMoved() const { return hasMoved; }

void King::setHasMoved(bool hasMoved) { this->hasMoved = hasMoved; }