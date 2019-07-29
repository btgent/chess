#include "coord.h"

bool Coord::operator==(const &Coord c) const {
  return ( (row == c.row) && (col == c.col) );
}

bool Coord::operator!=(const &Coord c) const {
  return !( *this == c );
}
