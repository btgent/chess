#include <memory>

struct Coord {
	int row, col;
	inline bool operator==(const &Coord c) {return ( (row == c.row) && (col == c.col) );}
	inline bool operator!=(const &Coord c) {return !( *this == c );}
};

enum Type { King, Queen, Rook, Bishop, Knight, Pawn };

enum Color { Black, White };

struct PastMove {
	Coord source;
	Coord dest;
	Type type;  //What type of piece moved
	bool check;  //If move puts the other colour in check
	std::unique_ptr<Piece> capture; //Store the piece that was captured (if any)
	std::unique_ptr<Piece> oldPromo; //Store the pawn when it gets promoted
	std::unique_ptr<Move> additional; //For castling
	inline PastMove(Coord source, Coord dest, Type type, bool check=false)
		: source{source}, dest{dest}, type{type}, check{check} {}
};

struct FutureMove {
	Coord source;
	Coord dest;
	bool isPromo;
	Type promoType;
	inline FutureMove(Coord source, Coord dest,
		bool isPromo=false, Type promoType=Type::Queen)
		: source{source}, dest{dest}, isPromo{isPromo}, promoType{promoType} {}
};
