#include "pastmove.h"
#include "piece.h"

PastMove::PastMove(Coord source, Coord dest, Type type, bool check=false)
  : source{source}, dest{dest}, type{type}, check{check} {}
