#include "king.h"

bool King::canMoveTo(const BoardState& board, const Position startPosition, const Position targetPosition) const
{
    // Starting case coordinates
    const auto y_Start{ startPosition.getY() };
    const auto x_Start{ startPosition.getX() };

    // Target case coordinates 
    const auto y_Target{ targetPosition.getY() };
    const auto x_Target{ targetPosition.getX() };

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