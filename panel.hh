#ifndef PANEL_HH
#define PANEL_HH

#include <vector>
#include <list>

using std::vector;
using std::list;

namespace tetris
{
    struct Position;
    class Unit;
    class Block;

    class PanelVisitor
    {
    public:
        virtual void visit(Unit * unit) = 0;
    };
    
    class Panel
    {
    public:
        Panel(int height, int width);
        ~Panel();

        void fix_block(const Block & block);
        void clear_full_lines();
        
        // Check if `pos' or position (y, x) is a legal point
        // that can hold a single point.
        bool is_legal(const Position & pos) const;
        bool is_legal(int y, int x) const;

        int height() const;
        int width() const;

        void traverse(PanelVisitor * visitor) const;

    private:
        int m_height;
        int m_width;
        list<vector<Unit *> > units;
        int score;
    };
}

#endif
