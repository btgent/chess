#include <iostream>
#include "window.h"

using namespace std;

enum Type {
  King, Queen, Rook, Bishop, Knight, Pawn
};

enum Colour { Black, White };

struct Coord {
  int row, col;
};

struct Piece {
  Coord pos;
  Type type;
  Colour colour;
};

int main (){
Xwindow w;
	int initx = 50;
	int inity = 50;
	int side = 50; //side for each square
	int bsize = 8;//myb.getSize(); //should equal to 8
	for (int i = 0; i < bsize; ++i) {  //i is height
		if (i % 2 == 0) {   //even rows
			for (int j = 0; j < bsize; ++j) { //white, Black repeated
				if (j % 2 == 0) {
					w.fillRectangle(initx + j*side, inity + i*side, side, side, Xwindow::White);
				}
				else {
					w.fillRectangle(initx + j * side, inity + i * side, side, side, Xwindow::Black);
				}
			}
		}
		else {   //odd rows
			for (int j = 0; j < bsize; ++j) {  //Black, White
				if (j % 2 == 0) {
					w.fillRectangle(initx + j * side, inity + i * side, side, side, Xwindow::Black);
				}
				else {
					w.fillRectangle(initx + j * side, inity + i * side, side, side, Xwindow::White);
				}
			}
		}
	}
  

Coord ck = {0, 0};
Coord cq = {2, 2};
Piece pk = {ck, Type::King, Colour::White};
Piece pq = {cq, Type::Queen, Colour::Black};
Piece parr[2] = {pk, pq};

	for (int i = 0; i < 2; ++i) {
		Piece thePiece = parr[i];
		int px = thePiece.pos.row;
		int py = thePiece.pos.col;
		Colour c = thePiece.colour;
//		switch (c) {
//			case Colour::Black: int Pcol = Xwindow::Red;
//			case Colour::White: int Pcol = Xwindow::Blue;
//		}

		Type t = thePiece.type;
		switch (t) {
	//		case Type::King: w.drawBigString(initx + px * side +25, inity + py * side +25, "King", Xwindow::Blue); break;
	//		case Type::Queen: w.drawBigString(initx + px * side +25, inity + py * side+25, "Queen", Xwindow::Blue); break;
			case Type::Rook: w.drawBigString(initx + px * side, inity + py * side, "R", Xwindow::Red); break;
			case Type::Bishop: w.drawBigString(initx + px * side, inity + py * side, "B", Xwindow::Red); break;
			case Type::Knight: w.drawBigString(initx + px * side, inity + py * side, "N", Xwindow::Red); break;
			case Type::Pawn: w.drawBigString(initx + px * side, inity + py * side, "P", Xwindow::Red); break;
		 case Type::King: w.drawBigString(initx + px * side +25, inity + py * side +25, "King", Xwindow::Blue); break;
                        case Type::Queen: w.drawBigString(initx + px * side +25, inity + py * side+25, "Queen", Xwindow::Blue); break;

		
		}
	}
	
	
  
  char c;
  cin >> c;
}
