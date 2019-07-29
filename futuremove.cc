#include "futuremove.h"

FutureMove::FutureMove(Coord source, Coord dest, bool isPromo=false, Type promoType=Type::Queen)
  : source{source}, dest{dest}, isPromo{isPromo}, promoType{promoType} {}
