#ifndef BLOCK_HH
#define BLOCK_HH

#include <vector>
#include <random>

#include "point.hh"

using std::mt19937;
using std::uniform_int_distribution;
using std::vector;
using std::pair;

namespace tetris
{
    class Panel;
    
    class Block
    {
    public:
        Block();

        // Move to left for one unit.
        // This function will first check if it's legal to move.
        // Next functions are of the same series.
        // 
        bool move_left(const Panel & panel);
        bool move_right(const Panel & panel);
        bool move_down(const Panel & panel);
        void rotate(const Panel & panel);
        void drop(const Panel & panel);
        
        const vector<Point> & get_points() const;

    protected:
        static const int DEGREE_0 = 0;
        static const int DEGREE_90 = 1;
        static const int DEGREE_180 = 2;
        static const int DEGREE_270 = 3;

        Point::Color generate_random_color() const;
        
        vector<Point> points;
        vector<vector<pair<int, int> > > rules;
        int angle;

    private:
        enum Direction
        {
            LEFT, RIGHT, DOWN
        };

        int find_next_rule(int rule) const;
        bool move(const Panel & panel, Direction direction);
        
        static mt19937 random_gen;
        static uniform_int_distribution<int> random_dis;
    };

    /**
     * Block of stick.
     *           *
     *           *
     *           *
     *           *
     * This block has two angles: vertical stick and horizonal stick.
     */
    class StickBlock : public Block
    {
    public:
        StickBlock(int y, int x);
    };

    /**
     * Block of four points consisting a square.
     *           **
     *           **
     **/
    class SquareBlock : public Block
    {
    public:
        SquareBlock(int y, int x);
    };
}

#endif
