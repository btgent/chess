#include "board.h"

class GraphicDisplay {
	const int boardSize; 
  public:
	GraphicDisplay();
	void drawBoard(const Board & myb);
	~GraphicDisplay();
};


