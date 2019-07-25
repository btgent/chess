#include "move.h"

Move::Move(Coord s, Coord d, Piece *c = nullptr, Piece *o = nullptr) :
	source{s},dest{d},capture{c},oddPromo{o} {}

Move::~Move() {
	delete capture;
	delete oldPromo;
}

Piece * getCapture() {
	return capture;
}

Piece * getoldPromo() {
	return oldPromo;
}
