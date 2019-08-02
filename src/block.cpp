#include "block.hpp"
#include "panel.hpp"
#include "drawer.hpp"

using std::random_device;
using std::make_pair;

#include <ncurses.h>

namespace tetris {
  static random_device rd;
  mt19937 RandomBlockFactory::random_gen(rd());
  uniform_int_distribution<int> RandomBlockFactory::random_dis(1, 7);

  Block * RandomBlockFactory::create_block(int y, int x) {
    Block * block = NULL;

    switch (random_dis(random_gen)) {
    case 1:
      block = new StickBlock(y, x);
      break;
    case 2:
      block = new SquareBlock(y, x);
      break;
    case 3:
      block = new TBlock(y, x);
      break;
    case 4:
      block = new ZBlock(y, x);
      break;
    case 5:
      block = new ReversedZBlock(y, x);
      break;
    case 6:
      block = new LBlock(y, x);
      break;
    case 7:
      block = new ReversedLBlock(y, x);
      break;
    }

    return block;
  }

  Block::Block() {
    angle = DEGREE_0;
    rules.resize(4);
  }

  bool Block::move_left(const Panel & panel) {
    return move(panel, LEFT);
  }

  bool Block::move_right(const Panel & panel) {
    return move(panel, RIGHT);
  }

  bool Block::move_down(const Panel & panel) {
    return move(panel, DOWN);
  }

  void Block::rotate(const Panel & panel) {
    if (angle >= 0) {
      int size = rules[angle].size();
      for (int i = 0; i < size; i++) {
        if (!panel.is_legal(
              units[i].position_after_move(rules[angle][i].first,
                                           rules[angle][i].second)))
          return ;
      }
      for (int i = 0; i < size; i++) {
        units[i].move(rules[angle][i].first, rules[angle][i].second);
      }
    }

    int next_angle = angle;
    for (int i = 0; i < 4; i++) {
      next_angle = (next_angle + 1) % 4;
      if (rules[next_angle].size() > 0) {
        angle = next_angle;
        break;
      }
    }
  }

  void Block::drop(const Panel & panel) {
    while (move_down(panel));
  }

  const vector<Unit> & Block::get_units() const {
    return units;
  }

  int Block::find_next_rule(int rule) const {
    return -1;
  }

  bool Block::move(const Panel & panel, Direction direction) {
    int var_y = 0;
    int var_x = 0;

    switch (direction) {
    case LEFT:
      var_x--;
      break;
    case RIGHT:
      var_x++;
      break;
    case DOWN:
      var_y++;
      break;
    }

    for (auto it = units.begin(); it != units.end(); it++) {
      if (!panel.is_legal(it->position_after_move(var_y, var_x)))
        return false;
    }

    for (auto it = units.begin(); it != units.end(); it++) {
      it->move(var_y, var_x);
    }

    return true;
  }

  StickBlock::StickBlock(int y, int x) : Block() {
    Unit::Color color = Unit::RED;
    units = {
      Unit(y, x, color),
      Unit(y+1, x, color),
      Unit(y+2, x, color),
      Unit(y+3, x, color),
    };
    rules[0] = {{2, 1}, {1, 0}, {0, -1}, {-1, -2}};
    rules[1] = {{-2, -1}, {-1, 0}, {0, 1}, {1, 2}};
  }

  SquareBlock::SquareBlock(int y, int x) : Block() {
    Unit::Color color = Unit::WHITE;
    units = {
      Unit(y, x, color),
      Unit(y, x+1, color),
      Unit(y+1, x, color),
      Unit(y+1, x+1, color),
    };
  }

  ZBlock::ZBlock(int y, int x) : Block() {
    Unit::Color color = Unit::YELLOW;
    units = {
      Unit(y, x, color),
      Unit(y, x+1, color),
      Unit(y+1, x+1, color),
      Unit(y+1, x+2, color),
    };
    rules[0] = {{1, 1}, {0, 0}, {-1, 1}, {-2, 0}};
    rules[1] = {{-1, -1}, {0, 0}, {1, -1}, {2, 0}};
  }

  ReversedZBlock::ReversedZBlock(int y, int x) : Block() {
    Unit::Color color = Unit::CYAN;
    units = {
      Unit(y, x, color),
      Unit(y, x-1, color),
      Unit(y+1, x-1, color),
      Unit(y+1, x-2, color),
    };
    rules[0] = {{0, -1}, {1, 0}, {0, 1}, {1, 2}};
    rules[1] = {{0, 1}, {-1, 0}, {0, -1}, {-1, -2}};
  }

  LBlock::LBlock(int y, int x) : Block() {
    Unit::Color color = Unit::GREEN;
    units = {
      Unit(y, x, color),
      Unit(y+1, x, color),
      Unit(y+2, x, color),
      Unit(y+2, x+1, color),
    };
    rules[0] = {{2, 0}, {0, 0}, {-1, 1}, {-1, 1}};
    rules[1] = {{-2, 0}, {-1, 1}, {0, 0}, {1, -1}};
    rules[2] = {{1, 1}, {2, 0}, {1, -1}, {0, -2}};
    rules[3] = {{-1, -1}, {-1, -1}, {0, 0}, {0, 2}};
  }

  ReversedLBlock::ReversedLBlock(int y, int x) : Block() {
    Unit::Color color = Unit::BLUE;
    units = {
      Unit(y, x, color),
      Unit(y+1, x, color),
      Unit(y+2, x, color),
      Unit(y+2, x-1, color),      
    };
    rules[0] = {{1, -1}, {1, -1}, {0, 0}, {0, 2}};
    rules[1] = {{1, 0}, {-1, 0}, {-2, -1}, {-2, -1}};
    rules[2] = {{-1, -1}, {0, 0}, {1, 1}, {2, 0}};
    rules[3] = {{-1, 2}, {0, 1}, {1, 0}, {0, -1}};
  }

  TBlock::TBlock(int y, int x) : Block() {
    Unit::Color color = Unit::WHITE;
    units = {
      Unit(y, x, color),
      Unit(y, x+1, color),
      Unit(y, x+2, color),
      Unit(y-1, x+1, color),
    };
    rules[0] = {{-1, 1}, {0, 0}, {1, -1}, {1, 1}};
    rules[1] = {{1, -1}, {0, 0}, {-1, 1}, {1, -1}};
    rules[2] = {{-1, 1}, {0, 0}, {1, -1}, {-1, -1}};
    rules[3] = {{1, -1}, {0, 0}, {-1, 1}, {-1, 1}};
  }
}
