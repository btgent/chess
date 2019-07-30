#include "pch.h"
#include "Human.h"


Human::Human():colour{ c } {}

Move Human::move(Board myb, Coord cod) {
	myb.move(cod);
}

Human::~Human() {}
