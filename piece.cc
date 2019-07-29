#include "piece.h"

Piece::Piece(Coord pos, Colour colour, Type type, bool firstMove)
  : pos{pos}, colour{colour}, type{type}, firstMove{firstMove} {}

Piece::~Piece() {}

Coord Piece::getPos() const { return pos; }

Colour Piece::getColour() const { return colour; }

Type Piece::getType() const { return type; }

bool isFirstMove() const { return firstMove; }

Piece::setPos(Coord dest) {
  pos.row = dest.row;
  pos.col = dest.col;
}
