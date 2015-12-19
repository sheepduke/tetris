#include "shape.hh"
#include "panel.hh"

using std::random_device;
using std::make_pair;

#include <ncurses.h>

namespace tetris
{
    static random_device rd;
    mt19937 Shape::random_gen(rd());
    uniform_int_distribution<int> Shape::random_dis(1, 6);

    Shape::Shape()
    {
        angle = DEGREE_0;
        rules.resize(4);
    }

    bool Shape::move_left(const Panel & panel)
    {
        return move(panel, LEFT);
    }

    bool Shape::move_right(const Panel & panel)
    {
        return move(panel, RIGHT);
    }

    bool Shape::move_down(const Panel & panel)
    {
        return move(panel, DOWN);
    }

    void Shape::rotate(const Panel & panel)
    {
        if (angle >= 0)
        {
            int size = rules[angle].size();
            for (int i = 0; i < size; i++)
            {
                if (!panel.is_legal(
                        blocks[i].position_after_move(rules[angle][i].first,
                                                      rules[angle][i].second)))
                    return ;
            }
            for (int i = 0; i < size; i++)
            {
                blocks[i].move(rules[angle][i].first, rules[angle][i].second);
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

    void Shape::drop(const Panel & panel)
    {
        while (move_down(panel));
    }

    const vector<Block> & Shape::get_blocks() const
    {
        return blocks;
    }
    
    Block::Color Shape::generate_random_color() const
    {
        switch (random_dis(random_gen))
        {
        case 1:
            return Block::WHITE;
        case 2:
            return Block::RED;
        case 3:
            return Block::GREEN;
        case 4:
            return Block::YELLOW;
        case 5:
            return Block::BLUE;
        case 6:
            return Block::CYAN;
        default:
            return Block::WHITE;
        }
    }

    int Shape::find_next_rule(int rule) const
    {
        return -1;
    }

    bool Shape::move(const Panel & panel, Direction direction)
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

        for (auto it = blocks.begin(); it != blocks.end(); it++)
        {
            if (!panel.is_legal(it->position_after_move(var_y, var_x)))
                return false;
        }

        for (auto it = blocks.begin(); it != blocks.end(); it++)
            it->move(var_y, var_x);

        return true;
    }

    // Stick Shape
    StickShape::StickShape(int y, int x) : Shape()
    {
        Block::Color color = generate_random_color();
        blocks.push_back(Block(y, x, color));
        blocks.push_back(Block(y-1, x, color));
        blocks.push_back(Block(y-2, x, color));
        blocks.push_back(Block(y-3, x, color));

        rules[0].push_back(make_pair(-1, 1));
        rules[0].push_back(make_pair(0, 0));
        rules[0].push_back(make_pair(1, -1));
        rules[0].push_back(make_pair(2, -2));

        rules[2].push_back(make_pair(1, -1));
        rules[2].push_back(make_pair(0, 0));
        rules[2].push_back(make_pair(-1, 1));
        rules[2].push_back(make_pair(-2, 2));
    }

    SquareShape::SquareShape(int y, int x) : Shape()
    {
        Block::Color color = generate_random_color();
        blocks.push_back(Block(y, x, color));
        blocks.push_back(Block(y-1, x, color));
        blocks.push_back(Block(y-1, x+1, color));
        blocks.push_back(Block(y, x+1, color));
    }
}
