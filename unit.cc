#include "unit.hh"

namespace tetris
{
    Unit::Unit(int y, int x, Color color)
    {

        pos.y = y;
        pos.x = x;
        m_color = color;
    }

    Position Unit::position_after_move(int units_y, int units_x) const
    {
        return Position(pos.y + units_y, pos.x + units_x * 2);
    }

    void Unit::move(int units_y, int units_x)
    {
        pos.y += units_y;
        pos.x += units_x * 2;
    }

    Unit::Color Unit::color() const
    {
        return m_color;
    }

    int Unit::x() const
    {
        return pos.x;
    }

    int Unit::y() const
    {
        return pos.y;
    }
}
