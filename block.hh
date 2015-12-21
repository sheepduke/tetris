#ifndef BLOCK_HH
#define BLOCK_HH

#include <vector>
#include <random>

#include "unit.hh"

using std::mt19937;
using std::uniform_int_distribution;
using std::vector;
using std::pair;

namespace tetris
{
    class Drawer;
    class Panel;
    class Block;

    /**
     * This class is used for creating blocks.
     */
    class RandomBlockFactory
    {
    public:
        // create a block with random type with y and x as height and width
        static Block * create_block(int y, int x);

    private:
        typedef int BlockType;
        
        static const BlockType STICK = 1;
        static const BlockType SQUARE = 2;

        static mt19937 random_gen;
        static uniform_int_distribution<int> random_dis;
    };

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

        const vector<Unit> & get_units() const;

    protected:
        static const int DEGREE_0 = 0;
        static const int DEGREE_90 = 1;
        static const int DEGREE_180 = 2;
        static const int DEGREE_270 = 3;

        vector<Unit> units;
        vector<vector<pair<int, int> > > rules;
        int angle;

    private:
        enum Direction
        {
            LEFT, RIGHT, DOWN
        };

        int find_next_rule(int rule) const;
        bool move(const Panel & panel, Direction direction);
    };

    /**
     * Block of stick.
     *           0
     *           1
     *           2
     *           3
     * This block has two angles: vertical stick and horizonal stick.
     */
    class StickBlock : public Block
    {
    public:
        StickBlock(int y, int x);
    };

    /**
     * Block of four units consisting a square.
     *           01
     *           23
     **/
    class SquareBlock : public Block
    {
    public:
        SquareBlock(int y, int x);
    };
}

#endif
