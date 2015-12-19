#include "panel.hh"
#include "score.hh"
#include "block.hh"

namespace tetris
{
    Panel::Panel(int max_y, int max_x)
    {
        this->max_y = max_y;
        this->max_x = max_x;
        blocks.resize(max_y);
        for (auto it = blocks.begin(); it != blocks.end(); it++)
        {
            it->assign(max_x, false);
        }
    }

    void Panel::clear_full_lines(Score & score)
    {
        int full_lines;
        score.handle_full_lines(full_lines);
    }

    bool Panel::is_legal(const Position & pos) const
    {
        return is_legal(pos.y, pos.x);
    }
    
    bool Panel::is_legal(int y, int x) const
    {
        if (y < 0 || y >= max_y || x < 0 || x >= max_x)
            return false;
        return !blocks[y][x];
    }

    int Panel::get_center_x() const
    {
        return max_x / 2;
    }
}
