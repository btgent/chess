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
	bool firstMove;  //so that undo() can restore a piece's first move
	std::unique_ptr<Piece> capture; //Store the piece that was captured (if any)
	std::unique_ptr<Piece> oldPromo; //Store the pawn when it gets promoted
	std::unique_ptr<PastMove> additional; //For castling
	
	PastMove(Coord source, Coord dest, Type type, bool check=false, bool firstMove=false);
};

#endif
