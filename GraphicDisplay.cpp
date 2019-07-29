#include "GraphicDisplay.h"
#include "xwindow.h"

GraphicDisplay::GraphicDisplay() {
}

//left top corner start with (50,50) and each rectangle is 50*50
void GraphicDisplay::drawBoard(const Board & myb) {  
	Xwindow w;
	int initx = 50;
	int inity = 50;
	int bsize = myb.getSize(); //should equal to 8
	for (int i = 0; i < bsize; ++i) {  //i is height
		if (i % 2 == 0) {
			for (int j = 0; j < bsize; ++j) { //white, Black
				if (j % 2 == 0) {
					w.fillRectangle(initx + i*50, inity + j*50, 50, 50, xWindow::White);
				}
				else {
					w.fillRectangle(initx + i * 50, inity + j * 50, 50, xWindow::Black);
				}
			}
		}
		else {
			for (int j = 0; j < bsize; ++j) {  //Black, White

			}
		}
	}
}

GraphicDisplay::~GraphicDisplay() {
}
