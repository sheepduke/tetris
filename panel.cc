#include "panel.hh"
#include "block.hh"
#include "unit.hh"

namespace tetris
{
    Panel::Panel(int height, int width)
    {
        m_height = height;
        m_width = width;
        units.resize(height);
        for (auto it = units.begin(); it != units.end(); it++)
        {
            it->assign(width, NULL);
        }
        score = 0;
    }

    Panel::~Panel()
    {
        for (auto row = units.begin(); row != units.end(); row++)
        {
            for (auto it = row->begin(); it != row->end(); it++)
            {
                delete *it;
                *it = NULL;
            }
            row->clear();
        }
    }
    
    void Panel::fix_block(const Block & block)
    {
        auto & new_units = block.get_units();
        for (auto it = new_units.begin(); it != new_units.end(); it++)
        {
            units[it->y()][it->x()] = new Unit(*it);
        }
        clear_full_lines();
    }

    void Panel::clear_full_lines()
    {
        int full_lines = 0;

        score += (10 + 5 * (full_lines - 1)) * full_lines;
    }

    bool Panel::is_legal(const Position & pos) const
    {
        return is_legal(pos.y(), pos.x());
    }
    
    bool Panel::is_legal(int y, int x) const
    {
        if (y < 0 || y >= m_height || x < 0 || x >= m_width)
            return false;
        return !units[y][x];
    }

    int Panel::height() const
    {
        return m_height;
    }

    int Panel::width() const
    {
        return m_width;
    }

    void Panel::traverse(PanelVisitor * visitor) const
    {
        for (auto row = units.begin(); row != units.end(); row++)
        {
            for (auto col = row->begin(); col != row->end(); col++)
            {
                visitor->visit(*col);
            }
        }
    }
}
