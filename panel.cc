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
        m_score = 0;
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
        int full_line_number = 0;

        for (auto row = units.begin(); row != units.end(); row++)
        {
            bool is_line_full = true;
            for (auto it = row->begin(); it != row->end(); it++)
            {
                // check if this line is full, set the flag to false if not
                if (*it == NULL)
                {
                    is_line_full = false;
                    break;
                }
            }
            // remove this line
            if (is_line_full)
            {
                full_line_number++;
                for (auto it = row->begin(); it != row->end(); it++)
                {
                    delete *it;
                    *it = NULL;
                }
                units.erase(row);
                row--;
                units.insert(units.begin(), *row);
            }
        }
        m_score += (10 + 5 * (full_line_number - 1)) * full_line_number;
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

    int Panel::score() const
    {
        return m_score;
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
