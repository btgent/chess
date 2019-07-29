#include <iostream>
#include "window.h"

using namespace std;

enum Type {
  King, Queen, Rook, Bishop, Knight, Pawn
};

enum Colour { Black, White };

struct Piece {
  Coord pos;
  Type type;
  Colour colour;
};

struct Coord {
	int row, col;
};

int main {
Xwindow w;
	int initx = 50;
	int inity = 50;
	int side = 50; //side for each square
	int bsize = myb.getSize(); //should equal to 8
	for (int i = 0; i < bsize; ++i) {  //i is height
		if (i % 2 == 0) {   //even rows
			for (int j = 0; j < bsize; ++j) { //white, Black repeated
				if (j % 2 == 0) {
					w.fillRectangle(initx + j*side, inity + i*side, side, side, xWindow::White);
				}
				else {
					w.fillRectangle(initx + j * side, inity + i * side, side, xWindow::Black);
				}
			}
		}
		else {   //odd rows
			for (int j = 0; j < bsize; ++j) {  //Black, White
				if (j % 2 == 0) {
					w.fillRectangle(initx + j * side, inity + i * side, side, side, xWindow::Black);
				}
				else {
					w.fillRectangle(initx + j * side, inity + i * side, side, xWindow::White);
				}
			}
		}
	}
  

Coord ck = {0, 0};
coord cq = {2, 2};
Piece pk = {ck, Type::King, Colour::White};
Piece pq = {cq, Type::Queen, Colour::Black};
Piece * parr[2] = {pk, pq};

	for (int i = 0; i < 2; ++i) {
		Piece thePiece = parr[i];
		int px = thePiece.pos.row;
		int py = thePiece.pos.col;
		Colour::c = thePiece.colour();
		switch (c) {
		case Black: Xwindow::Pcol = Xwindow::Red;
		case White: Xwindow::Pcol = Xwindow::Blue;
		}

		Type t = thePiece.type();
		switch (t) {
		case King: w.drawBigString(initx + px * size, inity + py * size, "K", Pcol);
		case Queen: w.drawBigString(initx + px * size, inity + py * size, "Q", Pcol);
		case Rook: w.drawBigString(initx + px * size, inity + py * size, "R", Pcol);
		case Bishop: w.drawBigString(initx + px * size, inity + py * size, "B", Pcol);
		case Knight: w.drawBigString(initx + px * size, inity + py * size, "N", Pcol);
		case Pawn: w.drawBigString(initx + px * size, inity + py * size, "P", Pcol);
		}
	
	
  
  char c;
  cin >> c;
}
