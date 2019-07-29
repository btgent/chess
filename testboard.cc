#include <iostream>
#include "window.h"

using namespace std;

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
  
  
  char c;
  cin >> c;
}
