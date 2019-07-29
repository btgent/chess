#ifndef PASTMOVE_H
#define PASTMOVE_H

#include "coord.h"
#include "type.h"
#include <memory>
class Piece;

struct PastMove {
	Coord source;
	Coord dest;
	Type type;  //What type of piece moved
	bool check;  //If move puts the other colour in check
	std::unique_ptr<Piece> capture; //Store the piece that was captured (if any)
	std::unique_ptr<Piece> oldPromo; //Store the pawn when it gets promoted
	std::unique_ptr<PastMove> additional; //For castling
};

#endif
