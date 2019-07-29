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

TextDisplay::~TextDisplay() {}

void TextDisplay::drawBoard(const Board & b) {
  for (auto temp : b.listPieces) {
    Colour c = temp->getColour();
    switch(c) {
      case White :  
        if (temp->getType() == King) {
          display[getPos().row-1][getPos().col-1] = 'K'; 
        }
        else if (temp->getType() == Queen) {
          display[getPos().row-1][getPos().col-1] = 'Q'; 
        }
        else if (temp->getType() == Bishop) {
          display[getPos().row-1][getPos().col-1] = 'B'; 
        }
        else if (temp->getType() == Knight) {
          display[getPos().row-1][getPos().col-1] = 'N'; 
        }
        else if (temp->getType() == Rook) {
          display[getPos().row-1][getPos().col-1] = 'R'; 
        }
        else if (temp->getType() == Pawn) {
          display[getPos().row-1][getPos().col-1] = 'P'; 
        }
        
      case Black :
        if (temp->getType() == King) {
          display[getPos().row-1][getPos().col-1] = 'k'; 
        }
        else if (temp->getType() == Queen) {
          display[getPos().row-1][getPos().col-1] = 'q'; 
        }
        else if (temp->getType() == Bishop) {
          display[getPos().row-1][getPos().col-1] = 'b'; 
        }
        else if (temp->getType() == Knight) {
          display[getPos().row-1][getPos().col-1] = 'n'; 
        }
        else if (temp->getType() == Rook) {
          display[getPos().row-1][getPos().col-1] = 'r'; 
        }
        else if (temp->getType() == Pawn) {
          display[getPos().row-1][getPos().col-1] = 'p'; 
        }
    }
  }
}
