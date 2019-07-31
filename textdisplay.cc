#include "textdisplay.h"
#include <iostream>
#include <vector>
#include "board.h"
#include "piece.h"

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
    const Piece *temp = &b.getPiece(i);
    Colour c = temp->getColour();
    switch(c) {
      case Colour::White :  
        if (temp->getType() == Type::King) {
          display[temp->getPos().row][temp->getPos().col] = 'K'; 
        }
        else if (temp->getType() == Type::Queen) {
          display[temp->getPos().row][temp->getPos().col] = 'Q'; 
        }
        else if (temp->getType() == Type::Bishop) {
          display[temp->getPos().row][temp->getPos().col] = 'B'; 
        }
        else if (temp->getType() == Type::Knight) {
          display[temp->getPos().row][temp->getPos().col] = 'N'; 
        }
        else if (temp->getType() == Type::Rook) {
          display[temp->getPos().row][temp->getPos().col] = 'R'; 
        }
        else if (temp->getType() == Type::Pawn) {
          display[temp->getPos().row][temp->getPos().col] = 'P'; 
        }
        break;
        
      case Colour::Black :
        if (temp->getType() == Type::King) {
          display[temp->getPos().row][temp->getPos().col] = 'k'; 
        }
        else if (temp->getType() == Type::Queen) {
          display[temp->getPos().row][temp->getPos().col] = 'q'; 
        }
        else if (temp->getType() == Type::Bishop) {
          display[temp->getPos().row][temp->getPos().col] = 'b'; 
        }
        else if (temp->getType() == Type::Knight) {
          display[temp->getPos().row][temp->getPos().col] = 'n'; 
        }
        else if (temp->getType() == Type::Rook) {
          display[temp->getPos().row][temp->getPos().col] = 'r'; 
        }
        else if (temp->getType() == Type::Pawn) {
          display[temp->getPos().row][temp->getPos().col] = 'p'; 
        }
        break;
    }
  }
  
  for (int i = n - 1; i >= 0; i--) {
    vector<char> temp = display[i];
    std::cout << i+1 << " ";
    for (auto c : temp) {
      std::cout << c; 
    }
    cout << std::endl;
  }
  std::cout << "  abcdefgh" << endl;
}
