#include "piece.h"

Piece::Piece(Coord pos, Colour colour, Type type, bool firstMove)
  : pos{pos}, colour{colour}, type{type}, firstMove{firstMove} {}

Piece::~Piece() {}

Coord Piece::getPos() const { return pos; }

Colour Piece::getColour() const { return colour; }

Type Piece::getType() const { return type; }

bool Piece::isFirstMove() const { return firstMove; }

void Piece::setPos(Coord dest) {
  pos.row = dest.row;
  pos.col = dest.col;
  firstMove = false;
}
