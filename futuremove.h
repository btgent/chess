#ifndef FUTUREMOVE_H
#define FUTUREMOVE_H

#include "coord.h"
#include "type.h"

struct FutureMove {
	Coord source;
	Coord dest;
	bool isPromo;
	Type promoType;
	
  FutureMove(Coord source, Coord dest, bool isPromo=false, Type promoType=Type::Queen);
};

#endif
