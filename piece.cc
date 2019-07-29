#include "piece.h"

Piece::Piece(Coord pos, Colour colour, Type type, bool firstMove)
  : pos{pos}, colour{colour}, type{type}, firstMove{firstMove} {}

Piece::~Piece() {}

Coord Piece::getPos() { return pos; }

Colour Piece::getColour() { return colour; }

Type Piece::getType() { return type; }

bool isFirstMove() { return firstMove; }

Piece::setPos(Coord dest) {
  pos.row = dest.row;
  pos.col = dest.col;
}
