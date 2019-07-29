#include "futuremove.h"

FutureMove::FutureMove(Coord source, Coord dest, bool isPromo, Type promoType)
  : source{source}, dest{dest}, isPromo{isPromo}, promoType{promoType} {}
