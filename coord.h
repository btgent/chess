#ifndef COORD_H
#define COORD_H

struct Coord {
  int row, col;
  
  bool operator==(const Coord&) const;
  bool operator!=(const Coord&) const;
};

#endif
