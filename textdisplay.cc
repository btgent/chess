#include "textdisplay.h"
#include <iostream>
#include <vector>

using namespace std;

TextDisplay::TextDisplay(int n) : boardSize(n) {}

TextDisplay::~TextDisplay() {}

void TextDisplay::drawBoard(const Board & b) {
  int n = b.getSize();
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
  
  for (int i=0; i<b.numPieces(); ++i) {
    Piece &temp = b.getPiece(i);
    Colour c = temp->getColour();
    switch(c) {
      case White :  
        if (temp->getType() == King) {
          display[getPos().row][getPos().col] = 'K'; 
        }
        else if (temp->getType() == Queen) {
          display[getPos().row][getPos().col] = 'Q'; 
        }
        else if (temp->getType() == Bishop) {
          display[getPos().row][getPos().col] = 'B'; 
        }
        else if (temp->getType() == Knight) {
          display[getPos().row][getPos().col] = 'N'; 
        }
        else if (temp->getType() == Rook) {
          display[getPos().row][getPos().col] = 'R'; 
        }
        else if (temp->getType() == Pawn) {
          display[getPos().row][getPos().col] = 'P'; 
        }
        break;
        
      case Black :
        if (temp->getType() == King) {
          display[getPos().row][getPos().col] = 'k'; 
        }
        else if (temp->getType() == Queen) {
          display[getPos().row][getPos().col] = 'q'; 
        }
        else if (temp->getType() == Bishop) {
          display[getPos().row][getPos().col] = 'b'; 
        }
        else if (temp->getType() == Knight) {
          display[getPos().row][getPos().col] = 'n'; 
        }
        else if (temp->getType() == Rook) {
          display[getPos().row][getPos().col] = 'r'; 
        }
        else if (temp->getType() == Pawn) {
          display[getPos().row][getPos().col] = 'p'; 
        }
        break;
    }
  }
  
  for (int i = n - 1; i >= 0; i--) {
    vector<std::char> temp = display[i];
    std::cout << i+1 << " ";
    for (auto c : temp) {
      std::cout << c; 
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  std::cout << "   abcdefgh" << endl;
}
