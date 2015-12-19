#ifndef DRAWER_HH
#define DRAWER_HH

namespace tetris
{
    class Panel;
    class Shape;
    class Block;
    
    class Drawer
    {
    public:
        Drawer();
        ~Drawer();

        void draw(const Shape & shape);
        void draw(const Block & block);

        void clear(const Shape & shape);

    private:
        static const int WHITE = 1;
        static const int RED = 2;
        static const int GREEN = 3;
        static const int YELLOW = 4;
        static const int BLUE = 5;
        static const int CYAN = 6;
    };
}

#endif
