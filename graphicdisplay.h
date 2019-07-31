#include "board.h"

class GraphicDisplay {
	const int boardSize = 8; 
  public:
	GraphicDisplay();
	void drawBoard(const Board & myb);
	~GraphicDisplay();
};


