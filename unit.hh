#ifndef UNIT_HH
#define UNIT_HH

namespace tetris
{
    class Position
    {
    public:
        Position() {}
        Position(int y, int x)
        {
            m_y = y;
            m_x = x;
        }

        int y() const
        {
            return m_y;
        }

        void set_y(int y)
        {
            m_y = y;
        }

        int x() const
        {
            return m_x;
        }

        void set_x(int x)
        {
            m_x = x;
        }

    private:
        int m_x;
        int m_y;
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
        Unit(const Unit & unit);

        Position position_after_move(int units_y, int units_x) const;
        void move(int units_y, int units_x);

        Color color() const;
        int x() const;
        int y() const;

        void set_x(int x);
        void set_y(int y);

    private:
        Color m_color;
        Position pos;
    };
}

#endif
