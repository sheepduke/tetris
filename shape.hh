#ifndef SHAPE_HH
#define SHAPE_HH

#include <vector>
#include <random>

#include "block.hh"

using std::mt19937;
using std::uniform_int_distribution;
using std::vector;
using std::pair;

namespace tetris
{
    class Panel;
    
    class Shape
    {
    public:
        Shape();

        // Move to left for one unit.
        // This function will first check if it's legal to move.
        // Next functions are of the same series.
        // 
        bool move_left(const Panel & panel);
        bool move_right(const Panel & panel);
        bool move_down(const Panel & panel);
        void rotate(const Panel & panel);
        void drop(const Panel & panel);
        
        const vector<Block> & get_blocks() const;

    protected:
        static const int DEGREE_0 = 0;
        static const int DEGREE_90 = 1;
        static const int DEGREE_180 = 2;
        static const int DEGREE_270 = 3;

        Block::Color generate_random_color() const;
        
        vector<Block> blocks;
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
     * Shape of stick.
     *           *
     *           *
     *           *
     *           *
     * This shape has two angles: vertical stick and horizonal stick.
     */
    class StickShape : public Shape
    {
    public:
        StickShape(int y, int x);
    };

    /**
     * Shape of four blocks consisting a square.
     *           **
     *           **
     **/
    class SquareShape : public Shape
    {
    public:
        SquareShape(int y, int x);
    };
}

#endif
