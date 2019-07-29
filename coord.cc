#include "coord.h"

bool Coord::operator==(const &Coord c) {
  return ( (row == c.row) && (col == c.col) );
}

bool Coord::operator!=(const &Coord c) {
  return !( *this == c );
}
