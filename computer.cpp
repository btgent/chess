#include <stdlib.h>
#include <time.h>
#include <move.h>
//#include <colour.h>

//vi = rand() % 100; //range 0 to 99

class Computer{
	Colour colour;
public:
	Computer(Colour c):colour{c} {}
	virtual Move move(Board) = 0;
};

class Computer1 : public Computer {
public:
	virtual Move move(Board);
};

Computer1::Computer1(Colour c) :Computer{ c } {}

Move Computer1::move(Board myb) override {
	for (auto &m : myb.allMoves(myb.getTurn())) {
		int psize = rand() % (myb.allMoves(myb.getTurn()).size());
		return myb.allMoves[psize];
	}
}

class Computer2 : public Computer {
public:
	virtual Move move(Board);
};

Computer2::Computer2(Colour c) :Computer{ c } {}

Move Computer2::move(Board myb) override {
	for (auto &m : myb.allMoves(myb.getTurn())) {
//		if (myb.getTurn() == Color::Black) {
		if (myb.pieceAt(m.dest)) { //capture case
			return m;
		}
		int psize = rand() % (myb.allMoves(myb.getTurn()).size());
		return myb.allMoves[psize];
	}
}

class Computer3 : public Computer {
public:
	virtual Move move(Board);
};

Computer3::Computer3(Colour c) :Computer{ c } {}

Move Computer3::move(Board myb) override {
	int i = 0;
	int psize = myb.allMoves(myb.getTurn()).size();
	vector<int> value = (psize, 0);
	for (auto &m : myb.allMoves(myb.getTurn())) { //move first and check if checkmate
		myb.move(m(source), m(dest));
		if (myb.getTurn() == Color::Black) {
			if (myb.check(Color::White)) {
				value.at(i) += 2;
			}
		}
		else { //White turn
			if (myb.check(Color::Black)) {
				value.at(i) += 2;
			}
		}
		if (myb.pieceAt(m.dest)) {
			value.at(i) += 2;
		}
		myb.undo();
	}
	int highest = 0;
	for (int j = 0; j < psize; ++j) {
		if (value.at(j) > highest) {
			highest = value.at(j);
		}
	}
	for (int j = 0; j < psize; ++j) {
		if (value.at(j) == highest) {
			return myb.allMoves(myb.getTurn()).at(j);
		}
	}
}
