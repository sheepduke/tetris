#include "block.hh"
#include "panel.hh"
#include "drawer.hh"

using std::random_device;
using std::make_pair;

#include <ncurses.h>

namespace tetris
{
    static random_device rd;
    mt19937 RandomBlockFactory::random_gen(rd());
    uniform_int_distribution<int> RandomBlockFactory::random_dis(1, 6);

    Block * RandomBlockFactory::create_block(int y, int x)
    {
        Block * block = NULL;

        // switch (random_dis(random_gen))
        // {
        // case STICK:
        //     block = new StickBlock(y, x);
        //     break;
        // case SQUARE:
        //     block = new SquareBlock(y, x);
        //     break;
        // default:
        //     block = new SquareBlock(y, x);
        //     break;
        // }

        int random = random_dis(random_gen);
        if (random % 2 == 0)
            block = new StickBlock(y, x);
        else
            block = new SquareBlock(y, x);

        return block;
    }

    Block::Block()
    {
        angle = DEGREE_0;
        rules.resize(4);
    }

    bool Block::move_left(const Panel & panel)
    {
        return move(panel, LEFT);
    }

    bool Block::move_right(const Panel & panel)
    {
        return move(panel, RIGHT);
    }

    bool Block::move_down(const Panel & panel)
    {
        return move(panel, DOWN);
    }

    void Block::rotate(const Panel & panel)
    {
        if (angle >= 0)
        {
            int size = rules[angle].size();
            for (int i = 0; i < size; i++)
            {
                if (!panel.is_legal(
                        units[i].position_after_move(rules[angle][i].first,
                                                      rules[angle][i].second)))
                    return ;
            }
            for (int i = 0; i < size; i++)
            {
                units[i].move(rules[angle][i].first, rules[angle][i].second);
            }
        }

        int next_angle = angle;
        for (int i = 0; i < 4; i++)
        {
            next_angle = (next_angle + 1) % 4;
            if (rules[next_angle].size() > 0)
            {
                angle = next_angle;
                break;
            }
        }
    }

    void Block::drop(const Panel & panel)
    {
        while (move_down(panel));
    }

    const vector<Unit> & Block::get_units() const
    {
        return units;
    }

    int Block::find_next_rule(int rule) const
    {
        return -1;
    }

    bool Block::move(const Panel & panel, Direction direction)
    {
        int var_y = 0;
        int var_x = 0;

        switch (direction)
        {
        case LEFT:
            var_x--;
            break;
        case RIGHT:
            var_x++;
            break;
        case DOWN:
            var_y++;
            break;
        }

        for (auto it = units.begin(); it != units.end(); it++)
        {
            if (!panel.is_legal(it->position_after_move(var_y, var_x)))
                return false;
        }

        for (auto it = units.begin(); it != units.end(); it++)
            it->move(var_y, var_x);

        return true;
    }

    // Stick Block
    StickBlock::StickBlock(int y, int x) : Block()
    {
        Unit::Color color = Unit::RED;
        units.push_back(Unit(y, x, color));
        units.push_back(Unit(y+1, x, color));
        units.push_back(Unit(y+2, x, color));
        units.push_back(Unit(y+3, x, color));

        rules[0].push_back(make_pair(2, 1));
        rules[0].push_back(make_pair(1, 0));
        rules[0].push_back(make_pair(0, -1));
        rules[0].push_back(make_pair(-1, -2));

        rules[2].push_back(make_pair(-2, -1));
        rules[2].push_back(make_pair(-1, 0));
        rules[2].push_back(make_pair(0, 1));
        rules[2].push_back(make_pair(1, 2));
    }

    SquareBlock::SquareBlock(int y, int x) : Block()
    {
        Unit::Color color = Unit::WHITE;
        units.push_back(Unit(y, x, color));
        units.push_back(Unit(y, x+1, color));
        units.push_back(Unit(y+1, x, color));
        units.push_back(Unit(y+1, x+1, color));
    }
}
