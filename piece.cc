#include "piece.h"

Piece::Piece(Coord pos, Colour colour, Type type): pos{pos}, colour{colour}, type{type}, firstMove{true} {}

Piece::~Piece() {}

Colour Piece::getColour() {
  return colour;
}

Type Piece::getType() {
  return type; 
}

Coord Piece::getPos() {
  return pos; 
}

Piece::setPos(Coord Pos) {
  pos.row = Pos.row;
  pos.col = Pos.col;
}
