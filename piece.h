#ifndef _PIECE_H_
#define _PIECE_H_

class Piece {
  Coord pos;
  Type type;
  Colour colour;
 public:
  bool virtual possibleMove(Coord) = 0;
  bool virtual possibleMove(int row, int col) = 0;
  void virtual setPos(Coord );
  

}

#endif
