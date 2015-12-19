#ifndef DRAWER_HH
#define DRAWER_HH

namespace tetris
{
    class Panel;
    class Block;
    class Point;
    
    class Drawer
    {
    public:
        Drawer();
        ~Drawer();

        void draw(const Block & block);
        void draw(const Point & point);

        void clear(const Block & block);

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
