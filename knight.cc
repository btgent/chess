#include "knight.h"
#include <vector>

Knight::Knight(Coord Pos, Colour colour): pos{Pos}, colour{colour} {
  type = Knight;
  if (Pos.col == 1) {
    if (Pos.row == 1) {
      Coord move1 {2, 3};
      moves.push_back(move1);
      Coord move2 {3, 2};
      moves.push_back(move2);
    }
    else if (Pos.row == 8) {
      Coord move1 {6, 2};
      moves.push_back(move1);
      Coord move2 {7, 3};
      moves.push_back(move2);
    }
    else if (Pos.row == 2) {
      
    ]
  }
}
