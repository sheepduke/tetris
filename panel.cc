#include "panel.hh"
#include "block.hh"
#include "unit.hh"

// debug
#include <fstream>

namespace tetris
{
    static std::ofstream fout("log");
    using std::endl;

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

        for (auto row = units.begin(); row != units.end();)
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
                fout << "Before: " << endl;
                print_test();
                for (auto it = row->begin(); it != row->end(); it++)
                {
                    delete *it;
                    *it = NULL;
                    fout << *it << endl;
                }
                fout << "After: " << endl;
                print_test();
                row->clear();
                units.erase(row);

                // vector<Unit *> vec;
                // vec.assign(m_width, NULL);
                units.insert(units.begin(), vector<Unit *>(m_width, NULL));
            }
            else
                row++;
        }
        // if there's any full lines, change all the Y value of each unit
        if (full_line_number > 0)
        {
            for (auto row = units.begin(); row != units.end(); row++)
                for (auto it = row->begin(); it != row->end(); it++)
                    if (*it)
                        (*it)->set_y((*it)->y() + full_line_number);
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
            for (auto it = row->begin(); it != row->end(); it++)
            {
                visitor->visit(*it);
            }
        }
    }

    // debug
    void Panel::print_test()
    {
        for (int i = 0; i < 21; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                fout << (is_legal(i, j) ? "0" : "#");
            }
            fout << endl;
        }
    }
}
