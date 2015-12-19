#ifndef POINT_HH
#define POINT_HH

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

    class Point
    {
    public:
        enum Color
        {
            WHITE, RED, GREEN, YELLOW, BLUE, CYAN
        };

        Point(int y, int x, Color color);

        Position position_after_move(int points_y, int points_x) const;
        void move(int points_y, int points_x);

        Color color() const;
        int x() const;
        int y() const;

    private:
        Color m_color;
        Position pos;
    };
}

#endif
