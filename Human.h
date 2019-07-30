#pragma once
class Human{
	Colour colour;
public:
	Human(Colour c);
	Move move(Board myb, Coord cod);
	~Human();
};

