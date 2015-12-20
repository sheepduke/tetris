#ifndef UNIT_HH
#define UNIT_HH

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

    class Unit
    {
    public:
        typedef int Color;
        
        static const Color WHITE = 1;
        static const Color RED = 2;
        static const Color GREEN = 3;
        static const Color YELLOW = 4;
        static const Color BLUE = 5;
        static const Color CYAN = 6;

        Unit(int y, int x, Color color);

        Position position_after_move(int units_y, int units_x) const;
        void move(int units_y, int units_x);

        Color color() const;
        int x() const;
        int y() const;

    private:
        Color m_color;
        Position pos;
    };
}

#endif
