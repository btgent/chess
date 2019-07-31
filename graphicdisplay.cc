#include "graphicdisplay.h"
#include "window.h"
#include "board.h"
#include "piece.h"

GraphicDisplay::GraphicDisplay() {
}

//left top corner start with (50,50) and each rectangle is 50*50
void GraphicDisplay::drawBoard(const Board & myb) {
	int initx = 50;
	int inity = 50;

	//draw boundary line for the board
	w.drawLine(initx, inity, initx, 450);
	w.drawLine(initx, inity, 450, inity);
	w.drawLine(initx, 450, 450, 450);
	w.drawLine(450, inity, 450, 450);

	int mids = 20; //distance of the string from the left top corner of the square
	int side = 50; //side for each square
	int bsize = myb.getSize(); //should equal to 8
	for (int i = 0; i < bsize; ++i) {  //i is height
		if (i % 2 == 0) {   //even rows
			for (int j = 0; j < bsize; ++j) { //white, Black repeated
				if (j % 2 == 0) {
					w.fillRectangle(initx + j * side, inity + i * side, side, side, Xwindow::White);
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
	int pnum = myb.numPieces();
	for (int i = 0; i < pnum; ++i) {
		const Piece &thePiece = myb.getPiece(i);
		int px = thePiece.getPos().col;
		int py = myb.getSize() - 1 - thePiece.getPos().row;
		Colour c = thePiece.getColour();
		//	switch (c) {
		//	case Black: Xwindow::Pcol = Xwindow::Red;
		//	case White: Xwindow::Pcol = Xwindow::Blue;
		//	}

		Type t = thePiece.getType();
		switch (t) {
		case Type::King:
			if (c == Colour::Black) {
				w.drawBigString(initx + px * side + mids, inity + py * side + mids, "K", Xwindow::Red); break;
			}
			else {
				w.drawBigString(initx + px * side + mids, inity + py * side + mids, "K", Xwindow::Blue); break;
			}
		case Type::Queen:
			if (c == Colour::Black) {
				w.drawBigString(initx + px * side + mids, inity + py * side + mids, "Q", Xwindow::Red); break;
			}
			else {
				w.drawBigString(initx + px * side + mids, inity + py * side + mids, "Q", Xwindow::Blue); break;
			}
		case Type::Rook:
			if (c == Colour::Black) {
				w.drawBigString(initx + px * side + mids, inity + py * side + mids, "R", Xwindow::Red); break;
			}
			else {
				w.drawBigString(initx + px * side + mids, inity + py * side + mids, "R", Xwindow::Blue); break;
			}
		case Type::Bishop:
			if (c == Colour::Black) {
				w.drawBigString(initx + px * side + mids, inity + py * side + mids, "B", Xwindow::Red); break;
			}
			else {
				w.drawBigString(initx + px * side + mids, inity + py * side + mids, "B", Xwindow::Blue); break;
			}
		case Type::Knight:
			if (c == Colour::Black) {
				w.drawBigString(initx + px * side + mids, inity + py * side + mids, "N", Xwindow::Red); break;
			}
			else {
				w.drawBigString(initx + px * side + mids, inity + py * side + mids, "N", Xwindow::Blue); break;
			}
		case Type::Pawn:
			if (c == Colour::Black) {
				w.drawBigString(initx + px * side + mids, inity + py * side + mids, "P", Xwindow::Red); break;
			}
			else {
				w.drawBigString(initx + px * side + mids, inity + py * side + mids, "P", Xwindow::Blue); break;
			}
		}
	}

}

GraphicDisplay::~GraphicDisplay() {
}
