#include <memory>

struct Coord {
	int row, col;
};

enum Type { King, Queen, Rook, Bishop, Knight, Pawn };

enum Color { Black, White };

struct PastMove {
	Coord source;
	Coord dest;
	std::unique_ptr<Piece> capture; //Piece * Capture; any dead Piece store
	std::unique_ptr<Piece> oldPromo; //Piece * oldPromo; store the pawn when it change to other type
	std::unique_ptr<Move> additional; //Move * additional; castle 
};

struct FutureMove {
	Coord source;
	Coord dest;
	bool isPromo;
	Type type;
};
