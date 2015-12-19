#include "block.hh"
#include "panel.hh"

using std::random_device;
using std::make_pair;

#include <ncurses.h>

namespace tetris
{
    static random_device rd;
    mt19937 Block::random_gen(rd());
    uniform_int_distribution<int> Block::random_dis(1, 6);

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
                        points[i].position_after_move(rules[angle][i].first,
                                                      rules[angle][i].second)))
                    return ;
            }
            for (int i = 0; i < size; i++)
            {
                points[i].move(rules[angle][i].first, rules[angle][i].second);
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

    const vector<Point> & Block::get_points() const
    {
        return points;
    }
    
    Point::Color Block::generate_random_color() const
    {
        switch (random_dis(random_gen))
        {
        case 1:
            return Point::WHITE;
        case 2:
            return Point::RED;
        case 3:
            return Point::GREEN;
        case 4:
            return Point::YELLOW;
        case 5:
            return Point::BLUE;
        case 6:
            return Point::CYAN;
        default:
            return Point::WHITE;
        }
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

        for (auto it = points.begin(); it != points.end(); it++)
        {
            if (!panel.is_legal(it->position_after_move(var_y, var_x)))
                return false;
        }

        for (auto it = points.begin(); it != points.end(); it++)
            it->move(var_y, var_x);

        return true;
    }

    // Stick Block
    StickBlock::StickBlock(int y, int x) : Block()
    {
        Point::Color color = generate_random_color();
        points.push_back(Point(y, x, color));
        points.push_back(Point(y-1, x, color));
        points.push_back(Point(y-2, x, color));
        points.push_back(Point(y-3, x, color));

        rules[0].push_back(make_pair(-1, 1));
        rules[0].push_back(make_pair(0, 0));
        rules[0].push_back(make_pair(1, -1));
        rules[0].push_back(make_pair(2, -2));

        rules[2].push_back(make_pair(1, -1));
        rules[2].push_back(make_pair(0, 0));
        rules[2].push_back(make_pair(-1, 1));
        rules[2].push_back(make_pair(-2, 2));
    }

    SquareBlock::SquareBlock(int y, int x) : Block()
    {
        Point::Color color = generate_random_color();
        points.push_back(Point(y, x, color));
        points.push_back(Point(y-1, x, color));
        points.push_back(Point(y-1, x+1, color));
        points.push_back(Point(y, x+1, color));
    }
}
