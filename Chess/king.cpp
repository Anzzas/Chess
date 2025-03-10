#include "king.h"
#include "board.h"

bool King::canMoveTo(const Board& board, const std::pair<size_t, size_t> startPosition, const std::pair<size_t, size_t> targetPosition) const
{
    // Starting case coordinates
    const auto [y_Start, x_Start] = startPosition;

    // Target case coordinates 
    const auto [y_Target, x_Target] = targetPosition;

    // Verifying the king doesn't put himself in Check
    if (!board.isKingInCheck(m_color, targetPosition))
    {
        // Calculate distances between start and target positions
        const int vertical_distance{ std::abs(static_cast<int>(y_Target) - static_cast<int>(y_Start)) };
        const int horizontal_distance{ std::abs(static_cast<int>(x_Target) - static_cast<int>(x_Start)) };

        // Check if the positions are different (king is actually moving)
        const bool is_moving{ (y_Target != y_Start || x_Target != x_Start) };

        // Kings can move exactly one square in any direction
        const bool is_valid_king_move{ (vertical_distance <= 1 && horizontal_distance <= 1 && is_moving) };

        if (is_valid_king_move)
            return true;
    }
    return false;
}

const bool& King::getHasMoved() const { return hasMoved; }

void King::setHasMoved(bool hasMoved) { this->hasMoved = hasMoved; }