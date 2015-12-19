#include "drawer.hh"
#include "panel.hh"
#include "shape.hh"
#include <ncurses.h>

using namespace std;
using namespace tetris;

int main()
{
    Drawer drawer;
    Panel panel(15, 20);
    Shape * shape = new StickShape(4, 4);

    drawer.draw(*shape);    
    refresh();

    int ch;
    while ((ch = getch()) != 'q')
    {
        drawer.clear(*shape);
        switch (ch)
        {
        case 'w':
            shape->rotate(panel);
            break;
        case 'a':
            shape->move_left(panel);
            break;
        case 'd':
            shape->move_right(panel);
            break;
        case 's':
            shape->move_down(panel);
            break;
        case ' ':
            shape->drop(panel);
        }
        drawer.draw(*shape);
    }
    
    refresh();
    
    return 0;
}
