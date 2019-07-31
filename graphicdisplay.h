#include "board.h"
#include "window.h"

class GraphicDisplay {
	const int boardSize = 8; 
	Xwindow w;
  public:
	GraphicDisplay();
	void drawBoard(const Board & myb);
	~GraphicDisplay();
};


