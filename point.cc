#include "point.hh"

namespace tetris
{
    Point::Point(int y, int x, Color color)
    {

        pos.y = y;
        pos.x = x;
        m_color = color;
    }

    Position Point::position_after_move(int points_y, int points_x) const
    {
        return Position(pos.y + points_y, pos.x + points_x * 2);
    }

    void Point::move(int points_y, int points_x)
    {
        pos.y += points_y;
        pos.x += points_x * 2;
    }

    Point::Color Point::color() const
    {
        return m_color;
    }

    int Point::x() const
    {
        return pos.x;
    }

    int Point::y() const
    {
        return pos.y;
    }
}
