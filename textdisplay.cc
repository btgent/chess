#include "textdisplay.h"
using vector::std;

TextDisplay::TextDisplay(int n) : boardSize(n) {
  for (int i = 0; i < n; i++) {
    vector<char> temp;
    for (int j = 0; j < n; j++) {
      if ((i % 2) == 0) {
        if ((j % 2) == 0) temp.push_back('_');
        else temp.push_back(' ');
      }
      else {
        if ((j % 2) == 0)  temp.push_back(' ');
        else temp.push_back('_');
      }
    }
    display.push_back(temp);
  }
}

void TextDisplay::drawBoard(const Board & b) {
  for (auto temp : b.listPieces) {
    Colour c = temp->getColour();
    switch(c) {
      case White :  if (W)
    
    }
  }
}
