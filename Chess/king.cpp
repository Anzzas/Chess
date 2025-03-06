#include "king.h"
#include "board.h"

bool King::canMoveTo(const Board& board, std::pair<size_t, size_t> startPosition, std::pair<size_t, size_t> targetPosition) const
{
    // Starting case coordinates
    const size_t x_Start{ startPosition.second };
    const size_t y_Start{ startPosition.first };
    // Target case coordinates 
    const Case& TargetCase{ board.getBoard()[targetPosition.first][targetPosition.second] };
    const size_t x_Target{ targetPosition.second };
    const size_t y_Target{ targetPosition.first };

    // Vérifier que la case cible est dans les limites de l'échiquier
    if (x_Target >= boardSettings::boardSize || y_Target >= boardSettings::boardSize) {
        return false;
    }

    // Vérifier que la case cible est soit vide, soit contient une pièce ennemie
    if (!TargetCase.isEmpty() && TargetCase.getPiece().getColor() == m_color)
        return false;

    else if (!TargetCase.isEmpty() && TargetCase.getPiece().getColor() != m_color)
        return true;

    // Vérifier que le roi ne se met pas lui-même en échec
    if (!board.isKingInCheck(m_color, targetPosition))
    {
        // Vérifier que le déplacement est d'une seule case dans n'importe quelle direction
        if (std::abs(static_cast<int>(y_Target) - static_cast<int>(y_Start)) <= 1 &&
            std::abs(static_cast<int>(x_Target) - static_cast<int>(x_Start)) <= 1 &&
            (y_Target != y_Start || x_Target != x_Start)) 
            return true;
    }
    return false;
}

const bool& King::getHasMoved() const { return hasMoved; }

void King::setHasMoved(bool hasMoved) { this->hasMoved = hasMoved; }