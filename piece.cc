#include "piece.h"

Piece::Piece(Coord pos, Type type, Colour colour): pos{pos}, colour{colour}, type{type}, firstMove(true) {}

Piece::~Piece() {}

ColourPiece::getColour() {
  return colour;
}

Piece::setPos(Coord Pos) {
  pos.row = Pos.row;
  pos.col = Pos.col;
}
