#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include <iostream>
#include <vector>
#include "board.h"

class TextDisplay {
  std::vector<std::vector<char>> display;
  const int boardSize; 
 public:
  TextDisplay(int n);
  void drawBoard(const Board & b);
};


#endif
