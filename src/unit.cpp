#include "unit.hpp"

namespace tetris {
  Unit::Unit(int y, int x, Color color) {

    pos.set_y(y);
    pos.set_x(x);
    m_color = color;
  }

  Unit::Unit(const Unit & unit) {
    m_color = unit.m_color;
    pos = unit.pos;
  }

  Position Unit::position_after_move(int units_y, int units_x) const {
    return Position(pos.y() + units_y, pos.x() + units_x);
  }

  void Unit::move(int units_y, int units_x) {
    pos.set_y(pos.y() + units_y);
    pos.set_x(pos.x() + units_x);
  }

  Unit::Color Unit::color() const {
    return m_color;
  }

  int Unit::x() const {
    return pos.x();
  }

  int Unit::y() const {
    return pos.y();
  }

  void Unit::set_x(int x) {
    pos.set_x(x);
  }

  void Unit::set_y(int y) {
    pos.set_y(y);
  }
}
