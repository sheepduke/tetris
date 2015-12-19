#ifndef BLOCK_HH
#define BLOCK_HH

namespace tetris
{
    struct Position
    {
        Position() {}
        Position(int y, int x)
        {
            this->y = y;
            this->x = x;
        }
        int x;
        int y;
    };

    class Block
    {
    public:
        enum Color
        {
            WHITE, RED, GREEN, YELLOW, BLUE, CYAN
        };

        Block(int y, int x, Color color);

        Position position_after_move(int blocks_y, int blocks_x) const;
        void move(int blocks_y, int blocks_x);

        Color color() const;
        int x() const;
        int y() const;

    private:
        Color m_color;
        Position pos;
    };
}

#endif
