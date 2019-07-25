#include "piece.h"

Piece::Piece(Coord pos, Type type, Colour colour): pos{pos}, type{type}, colour{colour} {}

Piece::setPos(Coord Pos) {
  pos->row = Pos->row;
  pos->col = Pos->col;
}
