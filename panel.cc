#include "panel.hh"
#include "block.hh"

namespace tetris
{
    Panel::Panel(int height, int width)
    {
        m_height = height;
        m_width = width;
        blocks.resize(height);
        for (auto it = blocks.begin(); it != blocks.end(); it++)
        {
            it->assign(width, false);
        }
        score = 0;
    }

    void Panel::clear_full_lines()
    {
        int full_lines;
        score += (10 + 5 * (full_lines - 1)) * full_lines;
    }

    bool Panel::is_legal(const Position & pos) const
    {
        return is_legal(pos.y, pos.x);
    }
    
    bool Panel::is_legal(int y, int x) const
    {
        if (y < 0 || y >= m_height || x < 0 || x >= m_width)
            return false;
        return !blocks[y][x];
    }

    int Panel::height() const
    {
        return m_height;
    }

    int Panel::width() const
    {
        return m_width;
    }
}
