struct Coord {
	int row, col;
};

enum Type { King, Queen, Rook, Bishop, Knight, Pawn };

enum Color { Black, White };

class Piece {};

struct Move {
	Coord source;
	Coord dest;
	Piece * Capture; //any dead Piece store
	Piece * oldPromo; //store the pawn when it change to other type
	Move * additional; //castle 
};
