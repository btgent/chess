#include "piece.h"

Piece::Piece(Coord pos, Type type, Colour colour, bool firstMove)
  : pos{pos}, type{type}, colour{colour}, firstMove{firstMove} {}

Piece::~Piece() {}

Coord Piece::getPos() { return pos; }

Type Piece::getType() { return type; }

Colour Piece::getColour() { return colour; }

bool isFirstMove() { return firstMove; }

Piece::setPos(Coord dest) {
  pos.row = dest.row;
  pos.col = dest.col;
}
