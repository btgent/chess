#include "pastmove.h"
#include "piece.h"

PastMove::PastMove(Coord source, Coord dest, Type type, bool check, bool firstMove)
  : source{source}, dest{dest}, type{type}, check{check}, firstMove{firstMove} {}
