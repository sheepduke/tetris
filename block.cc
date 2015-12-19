#include "block.hh"

namespace tetris
{
    Block::Block(int y, int x, Color color)
    {

        pos.y = y;
        pos.x = x;
        m_color = color;
    }

    Position Block::position_after_move(int blocks_y, int blocks_x) const
    {
        return Position(pos.y + blocks_y, pos.x + blocks_x * 2);
    }

    void Block::move(int blocks_y, int blocks_x)
    {
        pos.y += blocks_y;
        pos.x += blocks_x * 2;
    }

    Block::Color Block::color() const
    {
        return m_color;
    }

    int Block::x() const
    {
        return pos.x;
    }

    int Block::y() const
    {
        return pos.y;
    }
}
