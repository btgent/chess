#include <vector>
#include <memory>
struct Coord {
  int row, col;
  
  bool operator==(const Coord&) const;
  bool operator!=(const Coord&) const;
};
/////////////////////
bool Coord::operator==(const Coord& c) const {
  return ( (row == c.row) && (col == c.col) );
}

bool Coord::operator!=(const Coord& c) const {
  return !( *this == c );
}
/////////////////////
enum class Type {King, Queen, Rook, Bishop, Knight, Pawn};
enum class Colour {White, Black};
///////////////////////////////////////////////////////////
class Piece {
 protected:
  Coord pos;
  const Colour colour;
  const Type type;
  bool firstMove;
  
 public:
  Piece(Coord pos, Colour colour, Type type, bool firstMove=true);
  virtual ~Piece();
  
  Coord getPos() const;
  Colour getColour() const;
  Type getType() const;
  bool isFirstMove() const;
  void setPos(Coord);

  virtual bool possibleMove(Coord dest) const = 0;
  virtual bool possibleMove(int r, int c) const = 0;
  virtual std::vector<Coord> requiredEmpty(Coord dest) const = 0;
  virtual std::vector<Coord> requiredEmpty(int r, int c) const = 0;
  virtual std::vector<Coord> requiredOccupied(Coord dest) const = 0;
  virtual std::vector<Coord> requiredOccupied(int r, int c) const = 0;
};
///////////////////////////////////////////////////////////////
Piece::Piece(Coord pos, Colour colour, Type type, bool firstMove)
  : pos{pos}, colour{colour}, type{type}, firstMove{firstMove} {}

Piece::~Piece() {}

Coord Piece::getPos() const { return pos; }

Colour Piece::getColour() const { return colour; }

Type Piece::getType() const { return type; }

bool Piece::isFirstMove() const { return firstMove; }

void Piece::setPos(Coord dest) {
  pos.row = dest.row;
  pos.col = dest.col;
}

///////////////////////////////////////////////////////////////

class Pawn: public Piece {
 public:
  Pawn(Coord pos, Colour colour, bool firstMove=true);
  
  bool possibleMove(Coord dest) const override;
  bool possibleMove(int r, int c) const override;
  std::vector<Coord> requiredEmpty(Coord dest) const override;
  std::vector<Coord> requiredEmpty(int r, int c) const override;
  std::vector<Coord> requiredOccupied(Coord dest) const override;
  std::vector<Coord> requiredOccupied(int r, int c) const override;
};

///////////////////////////////////////////////////////
using std::vector;

Pawn::Pawn(Coord pos, Colour colour, bool firstMove)
  : Piece{pos, colour, Type::Pawn, firstMove} {}

bool Pawn::possibleMove(Coord dest) const {
  switch(colour) {
    case Colour::White :
      // forward move
      if (pos.col == dest.col) {
        if (dest.row == (pos.row + 1)) return true; 
        else if (firstMove && dest.row == (pos.row + 2)) return true;
      }
      // capture move
      else if (pos.col == (dest.col + 1) && dest.row == (pos.row + 1)) return true;
      else if (pos.col == (dest.col - 1) && dest.row == (pos.row + 1)) return true;
      break;
    
    case Colour::Black :
      if (pos.col == dest.col) {
        if (dest.row == (pos.row - 1)) return true; 
        else if (firstMove && dest.row == (pos.row - 2)) return true;
      }
      else if (pos.col == (dest.col + 1) && dest.row == (pos.row - 1)) return true;
      else if (pos.col == (dest.col - 1) && dest.row == (pos.row - 1)) return true;
  }
  // If all cases fail, then the move is generally not allowed
  return false;
}
bool Pawn::possibleMove(int r, int c) const {
  return possibleMove(Coord{.row=r, .col=c});
}

vector<Coord> Pawn::requiredEmpty(Coord dest) const {
  vector<Coord> v;
  // If move is not possible, return vector with current position
  if (!possibleMove(dest)) {
    v.push_back(pos);
    return v;
  }
  
  switch(colour) {
    case Colour::White :
      // forward move (general case does not require empty spaces
      //               for capture move)
      if (pos.col == dest.col) {
        for (int i = pos.row+1; i <= dest.row; i++) {
          Coord move{i, dest.col};
          v.push_back(move);
        }
      }
      break;
    
    case Colour::Black :
      if (pos.col == dest.col) {
        for (int i = pos.row-1; i >= dest.row; i--) {
          Coord move{i, dest.col};
          v.push_back(move);
        }
      }
      break;
  }
  return v;
}
vector<Coord> Pawn::requiredEmpty(int r, int c) const {
  return requiredEmpty(Coord{.row=r, .col=c});
}
                 
vector<Coord> Pawn::requiredOccupied(Coord dest) const {
  vector<Coord> v;
  // If move is not possible, return vector with current position
  if (!possibleMove(dest)) {
    v.push_back(pos);
    return v;
  }
  // If the move is a capture move, add dest must be occupied
  // (enpassant is a special case not covered by this method)
  if (pos.col != dest.col) {
    v.push_back(dest);
  }
  return v;
}
vector<Coord> Pawn::requiredOccupied(int r, int c) const {
  return requiredOccupied(Coord{.row=r, .col=c});
}
////////////////////////////////////////////////////
class Knight: public Piece {
 public:
  Knight(Coord pos, Colour colour, bool firstMove=true);
  
  bool possibleMove(Coord dest) const override;
  bool possibleMove(int r, int c) const override;
  std::vector<Coord> requiredEmpty(Coord dest) const override;
  std::vector<Coord> requiredEmpty(int r, int c) const override;
  std::vector<Coord> requiredOccupied(Coord dest) const override;
  std::vector<Coord> requiredOccupied(int r, int c) const override;
};

////////////////////////////////////////////////////

Knight::Knight(Coord pos, Colour colour, bool firstMove)
  : Piece{pos, colour, Type::Knight, firstMove} {}

bool Knight::possibleMove(Coord dest) const {
  if ((dest.col == pos.col + 2) || (dest.col == pos.col - 2)) {
    if ((dest.row == pos.row + 1) || (dest.row == pos.row - 1)) return true;
  }
  if ((dest.col == pos.col + 1) || (dest.col == pos.col - 1)) {
    if ((dest.row == pos.row + 2) || (dest.row == pos.row - 2)) return true;
  }
  return false;
}
bool Knight::possibleMove(int r, int c) const {
  return possibleMove(Coord{.row=r, .col=c});
}

vector<Coord> Knight::requiredEmpty(Coord dest) const {
  vector<Coord> v;
  // as long as the move is possible, knight doesn't need to traverse any squares
  if (!possibleMove(dest)) {
    v.push_back(pos);
  }
  return v;
}
vector<Coord> Knight::requiredEmpty(int r, int c) const {
  return requiredEmpty(Coord{.row=r, .col=c});
}

vector<Coord> Knight::requiredOccupied(Coord dest) const {
  vector<Coord> v;
  // all standard pieces except pawn don't require an enemy piece to move
  // in a certain way
  if  (!possibleMove(dest)) {
    v.push_back(pos);
  }
  return v;
}
vector<Coord> Knight::requiredOccupied(int r, int c) const {
  return requiredOccupied(Coord{.row=r, .col=c});
}
//////////////////////////////////////////////////////////////////
class Bishop: public Piece {
 public:
  Bishop(Coord pos, Colour colour, bool firstMove=true);
  
  bool possibleMove(Coord dest) const override;
  bool possibleMove(int r, int c) const override;
  std::vector<Coord> requiredEmpty(Coord dest) const override;
  std::vector<Coord> requiredEmpty(int r, int c) const override;
  std::vector<Coord> requiredOccupied(Coord dest) const override;
  std::vector<Coord> requiredOccupied(int r, int c) const override;
};
//////////////////////////////////////////////////////////////////
Bishop::Bishop(Coord pos, Colour colour, bool firstMove)
  : Piece{pos, colour, Type::Bishop, firstMove} {}

int abs(int i)  {return (i>0) ? i : -i;}

bool Bishop::possibleMove(Coord dest) const {
  if ((dest.row == pos.row) && (dest.col == pos.col)) return false;
  else if (abs(dest.row - pos.row) == abs(dest.col - pos.col)) return true;
  return false;
}
bool Bishop::possibleMove(int r, int c) const {
  return possibleMove(Coord{.row=r, .col=c});
}

vector<Coord> Bishop::requiredEmpty(Coord dest) const {
  vector<Coord> v;
  if (!possibleMove(dest)) {
    v.push_back(pos);
    return v;
  }
  if (dest.row > pos.row) {
    if (dest.col > pos.col) {
      // NE
      for (int i = 1; (pos.row + i) < dest.row; i++) {
        Coord move {pos.row + i, pos.col + i};
        v.push_back(move);
      }
    } else {
      // NW
      for (int i = 1; (pos.row + i) < dest.row; i++) {
        Coord move {pos.row + i, pos.col - i};
        v.push_back(move);
      }
    }
  } else {
    if (dest.col > pos.col) {
      // SE
      for (int i = 1; (pos.row - i) > dest.row; i++) {
        Coord move {pos.row - i, pos.col + i};
        v.push_back(move);
      }
    } else {
      // SW
      for (int i = 1; (pos.row - i) > dest.row; i++) {
        Coord move {pos.row - i, pos.col - i};
        v.push_back(move);
      }
    }
  }
  return v;
}
vector<Coord> Bishop::requiredEmpty(int r, int c) const {
  return requiredEmpty(Coord{.row=r, .col=c});
}

vector<Coord> Bishop::requiredOccupied(Coord dest) const {
  vector<Coord> v;
  // all standard pieces except pawn don't require an enemy piece to move
  // in a certain way
  if  (!possibleMove(dest)) {
    v.push_back(pos);
  }
  return v;
}
vector<Coord> Bishop::requiredOccupied(int r, int c) const {
  return requiredOccupied(Coord{.row=r, .col=c});
}
//////////////////////////////////////////////////////////////////
class Rook: public Piece {
 public:
  Rook(Coord pos, Colour colour, bool firstMove=true);
  
  bool possibleMove(Coord dest) const override;
  bool possibleMove(int r, int c) const override;
  std::vector<Coord> requiredEmpty(Coord dest) const override;
  std::vector<Coord> requiredEmpty(int r, int c) const override;
  std::vector<Coord> requiredOccupied(Coord dest) const override;
  std::vector<Coord> requiredOccupied(int r, int c) const override;
};
//////////////////////////////////////////////////////////////////
Rook::Rook(Coord pos, Colour colour, bool firstMove)
  : Piece{pos, colour, Type::Rook, firstMove} {}

bool Rook::possibleMove(Coord dest) const {
  if ((dest.row == pos.row) && (dest.col == pos.col)) return false;
  else if ((dest.row == pos.row) || (dest.col == pos.col)) return true;
  else return false;
}
bool Rook::possibleMove(int r, int c) const {
  return possibleMove(Coord{.row=r, .col=c});
}

vector<Coord> Rook::requiredEmpty(Coord dest) const {
  vector<Coord> v;
  if (!possibleMove(dest)) {
    v.push_back(pos);
    return v;
  }
  if (pos.row == dest.row) {
    if (pos.col < dest.col) {
      // E
      for (int i = pos.col + 1; i < dest.col; i++) {
        Coord move {pos.row, i};
        v.push_back(move);
      }
    } else {
      // W
      for (int i = pos.col - 1; i > dest.col; i--) {
        Coord move {pos.row, i};
        v.push_back(move);
      }
    }
  } else {
    if (pos.row < dest.row) {
      // N
      for (int i = pos.row + 1; i < dest.row; i++) {
        Coord move {i, pos.col};
        v.push_back(move);
      }
    } else {
      // S
      for (int i = pos.row - 1; i > dest.row; i--) {
        Coord move {i, pos.col};
        v.push_back(move);
      }
    }
  }
  return v;
}
vector<Coord> Rook::requiredEmpty(int r, int c) const {
  return requiredEmpty(Coord{.row=r, .col=c});
}

vector<Coord> Rook::requiredOccupied(Coord dest) const {
  vector<Coord> v;
  // all standard pieces except pawn don't require an enemy piece to move
  // in a certain way
  if  (!possibleMove(dest)) {
    v.push_back(pos);
  }
  return v;
}
vector<Coord> Rook::requiredOccupied(int r, int c) const {
  return requiredOccupied(Coord{.row=r, .col=c});
}

//////////////////////////////////////////////////////////////////
class Queen: public Piece {
 public:
  Queen(Coord pos, Colour colour, bool firstMove=true);
  
  bool possibleMove(Coord dest) const override;
  bool possibleMove(int r, int c) const override;
  std::vector<Coord> requiredEmpty(Coord dest) const override;
  std::vector<Coord> requiredEmpty(int r, int c) const override;
  std::vector<Coord> requiredOccupied(Coord dest) const override;
  std::vector<Coord> requiredOccupied(int r, int c) const override;
};
/////////////////////////////////////////////////////////////////
Queen::Queen(Coord pos, Colour colour, bool firstMove)
  : Piece{pos, colour, Type::Queen, firstMove} {}


bool Queen::possibleMove(Coord dest) const {
  if ((dest.row == pos.row) && (dest.col == pos.col)) return false;
  else if (abs(dest.row - pos.row) == abs(dest.col - pos.col)) return true;
  else if ((pos.row == dest.row) || (pos.col == dest.col)) return true;
  return false;
}
bool Queen::possibleMove(int r, int c) const {
  return possibleMove(Coord{.row=r, .col=c});
}

vector<Coord> Queen::requiredEmpty(Coord dest) const {
  vector<Coord> v;
  if (!possibleMove(dest)) {
    v.emplace_back(pos);
    return v;
  }
  
  if (pos.row < dest.row) {
    if (pos.col < dest.col) {
      // NE
      for (int i = 1; (pos.row + i) < dest.row; i++) {
        Coord move {pos.row + i, pos.col + i};
        v.push_back(move);
      }
    } else if (pos.col == dest.col) {
      // N
      for (int i = pos.row + 1; i < dest.row; i++) {
        Coord move {i, pos.col};
        v.push_back(move);
      }
    } else {
      // NW
      for (int i = 1; (pos.row + i) < dest.row; i++) {
        Coord move {pos.row + i, pos.col - i};
        v.push_back(move);
      }
    }
  } else if (pos.row == dest.row) {
    if (pos.col < dest.col) {
      // E
      for (int i = pos.col + 1; i < dest.col; i++) {
        Coord move {pos.row, i};
        v.push_back(move);
      }
    } else {
      // W
      for (int i = pos.col - 1; i > dest.col; i--) {
        Coord move {pos.row, i};
        v.push_back(move);
      }
    }
  } else {
    if (pos.col < dest.col) {
      // SE
      for (int i = 1; (pos.row - i) > dest.row; i++) {
        Coord move {pos.row - i, pos.col + i};
        v.push_back(move);
      }
    } else if (pos.col == dest.col) {
      // S
      for (int i = pos.row - 1; i > dest.row; i--) {
        Coord move {i, pos.col};
        v.push_back(move);
      }
    } else {
      // SW
      for (int i = 1; (pos.row - i) > dest.row; i++) {
        Coord move {pos.row - i, pos.col - i};
        v.push_back(move);
      }
    }
  }
  return v;
}
vector<Coord> Queen::requiredEmpty(int r, int c) const {
  return requiredEmpty(Coord{.row=r, .col=c});
}

vector<Coord> Queen::requiredOccupied(Coord dest) const {
  vector<Coord> v;
  // all standard pieces except pawn don't require an enemy piece to move
  // in a certain way
  if  (!possibleMove(dest)) {
    v.push_back(pos);
  }
  return v;
}
vector<Coord> Queen::requiredOccupied(int r, int c) const {
  return requiredOccupied(Coord{.row=r, .col=c});
}
/////////////////////////////////////////////////////////////////
class King: public Piece {
 public:
  King(Coord pos, Colour colour, bool firstMove=true);
  
  bool possibleMove(Coord dest) const override;
  bool possibleMove(int r, int c) const override;
  std::vector<Coord> requiredEmpty(Coord dest) const override;
  std::vector<Coord> requiredEmpty(int r, int c) const override;
  std::vector<Coord> requiredOccupied(Coord dest) const override;
  std::vector<Coord> requiredOccupied(int r, int c) const override;
};
/////////////////////////////////////////////////////////////////
King::King(Coord pos, Colour colour, bool firstMove)
  : Piece{pos, colour, Type::King, firstMove} {}

bool King::possibleMove(Coord dest) const {
  if ((dest.row == pos.row) && (dest.col == pos.col)) return false;
  if ( (abs(pos.row - dest.row) <= 1) && (abs(pos.col - dest.col) <= 1) ) return true;
  return false;
}
bool King::possibleMove(int r, int c) const {
  return possibleMove(Coord{.row=r, .col=c});
}

vector<Coord> King::requiredEmpty(Coord dest) const {
  vector<Coord> v;
  // as long as the move is possible, king doesn't need to traverse any squares
  if (!possibleMove(dest)) {
    v.push_back(pos);
  }
  return v;
}
vector<Coord> King::requiredEmpty(int r, int c) const {
  return requiredEmpty(Coord{.row=r, .col=c});
}

vector<Coord> King::requiredOccupied(Coord dest) const {
  vector<Coord> v;
  // all standard pieces except pawn don't require an enemy piece to move
  // in a certain way
  if  (!possibleMove(dest)) {
    v.push_back(pos);
  }
  return v;
}
vector<Coord> King::requiredOccupied(int r, int c) const {
  return requiredOccupied(Coord{.row=r, .col=c});
}
/////////////////////////////////////////////////////////////////
class Piece;

struct PastMove {
	Coord source;
	Coord dest;
	Type type;  //What type of piece moved
	bool check;  //If move puts the other colour in check
	std::unique_ptr<Piece> capture; //Store the piece that was captured (if any)
	std::unique_ptr<Piece> oldPromo; //Store the pawn when it gets promoted
	std::unique_ptr<PastMove> additional; //For castling
	
	PastMove(Coord source, Coord dest, Type type, bool check=false);
};
PastMove::PastMove(Coord source, Coord dest, Type type, bool check)
  : source{source}, dest{dest}, type{type}, check{check} {}
///////////////////
struct FutureMove {
	Coord source;
	Coord dest;
	bool isPromo;
	Type promoType;
	
  FutureMove(Coord source, Coord dest, bool isPromo=false, Type promoType=Type::Queen);
};
FutureMove::FutureMove(Coord source, Coord dest, bool isPromo, Type promoType)
  : source{source}, dest{dest}, isPromo{isPromo}, promoType{promoType} {}
//////////////////////////////////////////////////////////////////////////////////////
class Board {
  std::vector<std::unique_ptr<Piece>> listPieces;
  std::vector<PastMove> stackMove;
  Piece *kingWhite;
  Piece *kingBlack;
  Colour turn;
  Colour moveFirst;
  const int size;

  void forceMove(Coord, Coord);
  void forceMove(int, int, int, int);
  int index(Coord);
  int index(int, int);
  void nextColour();
  void prevColour();
  void undo(PastMove &);
  bool canMove(Piece &, Coord dest);
  void move(Coord, Coord, Type, Colour);

 public:
  Board(std::vector<std::unique_ptr<Piece>>&&, Colour, int size=8);
  Board(const Board &b);
  Board &operator=(const Board &b) = delete;
  ~Board();

  void undo();
  void move(FutureMove);
  void move(Coord, Coord, Type=Type::Queen);
  void move(int, int, int, int, Type=Type::Queen);
  bool check(Colour);
  bool checkmate(Colour);
  bool pieceAt(Coord);
  bool pieceAt(int, int);
  bool pieceAt(Coord, Colour);
  bool pieceAt(int, int, Colour);
  bool outOfBounds(Coord);
  bool outOfBounds(int, int);
  vector<FutureMove> allMoves(Colour);
  int numAllMoves(Colour);
  bool isPromo(Coord, Coord);
  bool isPromo(int, int, int, int);
  int numPieces() const;
  const Piece &getPiece(int i) const;
  int numMoves() const;
  const PastMove &getMove(int i) const;
  Colour getTurn() const;
  int getSize() const;
};
///////////////////////////////
using namespace std;
void Board::forceMove(Coord source, Coord dest) {
  // Check if piece exists at source before moving
  if (!pieceAt(source)) throw 1;
  stackMove.emplace_back(PastMove{source, dest, Type::Queen});
  if (pieceAt(dest)) {
    int k = index(dest);
    stackMove.back().capture = std::move(listPieces[k]);
    listPieces.erase(listPieces.begin()+k);
  }
  listPieces[index(source)]->setPos(dest);
  nextColour();
}
void Board::forceMove(int sr, int sc, int dr, int dc) {
  forceMove(Coord{.row=sr, .col=sc}, Coord{.row=dr, .col=dc});
}

// Find index in listPieces where there is a piece with
// the passed coordinates
int Board::index(Coord loc) {
  int i=0;
  for (auto &p : listPieces) {
    if (p->getPos() == loc) return i;
    ++i;
  }
  throw 1;
}
int Board::index(int r, int c) {
  return index(Coord{.row=r, .col=c});
}

// change turns
void Board::nextColour() {
  switch (turn) {
  case Colour::White :
    turn = Colour::Black;
    break;
  case Colour::Black :
    turn = Colour::White;
  }
}
void Board::prevColour() {
  switch (turn) {
  case Colour::White :
    turn = Colour::Black;
    break;
  case Colour::Black :
    turn = Colour::White;
  }
}

// undo a specific move ( used by undo() )
// Does not change whose turn it is (because for compound moves (eg. castle),
// this function can be called multiple times for one turn)
void Board::undo(PastMove &m) {
  // undo m.additional first
  if (m.additional.get() != nullptr) undo(*m.additional);
  int i = index(m.dest);
  // replace the promotion (if there is one)
  if (m.oldPromo.get() != nullptr) {
    listPieces.erase(listPieces.begin()+i);
    listPieces.emplace_back(std::move(m.oldPromo));
    i = listPieces.size() - 1;
  }
  // undo the move
  listPieces[i]->setPos(m.source);
  // replace the capture
  listPieces.emplace_back(std::move(m.capture));
}

// see if Piece can move to Coord ( used by check(...), move(...) )
// Does not check if final positions leave king in check
bool Board::canMove(Piece &p, Coord dest) {
  // Check that dest is within boundaries
  if (outOfBounds(dest)) return false;
  
  // Check for special moves
  Coord pCoord = p.getPos();
  // (enpassant)
  if (p.getType() == Type::Pawn) {
    Coord left_enpassant{.row=pCoord.row, .col=pCoord.col-1};
    Coord right_enpassant{.row=pCoord.row, .col=pCoord.col+1};
    switch (p.getColour()) {
    case Colour::White :
      // Check that dest is in the right place and is not occupied
      if (!(dest.row == pCoord.row+1
        && (dest.col == pCoord.col+1 || dest.col == pCoord.col-1)
        && !pieceAt(dest))) break;
      // Check for left_enpassant
      if (pieceAt(left_enpassant)
        && !pieceAt(left_enpassant, p.getColour())) {
        Piece &c = *listPieces[index(left_enpassant)];
        if (c.getType() == Type::Pawn && stackMove.back().dest == c.getPos()
          && stackMove.back().source.row == c.getPos().row+2) return true;
      }
      // Check for right_enpassant
      if (pieceAt(right_enpassant)
        && !pieceAt(right_enpassant, p.getColour())) {
        Piece &c = *listPieces[index(right_enpassant)];
        if (c.getType() == Type::Pawn && stackMove.back().dest == c.getPos()
          && stackMove.back().source.row == c.getPos().row+2) return true;
      }
      break;
    case Colour::Black :
      // Check that dest is in the right place and is not occupied
      if (!(dest.row == pCoord.row-1
        && (dest.col == pCoord.col+1 || dest.col == pCoord.col-1)
        && !pieceAt(dest))) break;
      // Check for left_enpassant
      if (pieceAt(left_enpassant)
        && !pieceAt(left_enpassant, p.getColour())) {
        Piece &c = *listPieces[index(left_enpassant)];
        if (c.getType() == Type::Pawn && stackMove.back().dest == c.getPos()
          && stackMove.back().source.row == c.getPos().row-2) return true;
      }
      // Check for right_empassant
      if (pieceAt(right_enpassant)
        && !pieceAt(right_enpassant, p.getColour())) {
        Piece &c = *listPieces[index(right_enpassant)];
        if (c.getType() == Type::Pawn && stackMove.back().dest == c.getPos()
          && stackMove.back().source.row == c.getPos().row-2) return true;
      }
    }
  }
  // (castle)
  if (p.getType() == Type::King && p.isFirstMove() && !check(p.getColour())) {
    // Check left castle
    if (dest.row == pCoord.row && dest.col == pCoord.col-2
      && pieceAt(pCoord.row, pCoord.col-4, p.getColour())) {
      Piece &r = *listPieces[index(pCoord.row, pCoord.col-4)];
      if (r.getType() == Type::Rook && r.isFirstMove()
        && !pieceAt(pCoord.row, pCoord.col-1)
        && !pieceAt(pCoord.row, pCoord.col-2)
        && !pieceAt(pCoord.row, pCoord.col-3)) {
        forceMove(pCoord.row, pCoord.col, pCoord.row, pCoord.col-1);
        if (!check(p.getColour())) {
          undo();
          return true;
        }
        undo();
      }
    }
    // Check right castle
    if (dest.row == pCoord.row && dest.col == pCoord.col+2
      && pieceAt(pCoord.row, pCoord.col+3, p.getColour())) {
      Piece &r = *listPieces[index(pCoord.row, pCoord.col+3)];
      if (r.getType() == Type::Rook && r.isFirstMove()
        && !pieceAt(pCoord.row, pCoord.col+1)
        && !pieceAt(pCoord.row, pCoord.col+2)) {
        forceMove(pCoord.row, pCoord.col, pCoord.row, pCoord.col+1);
        if (!check(p.getColour())) {
          undo();
          return true;
        }
        undo();
      }
    }
  }
  
  
  // (general case)
  // dest must be in a possible direction for p to move in
  if (!p.possibleMove(dest)) return false;
  // the required empy spots must be empty
  for (auto &c :  p.requiredEmpty(dest)) {
    if (pieceAt(c)) return false;
  }
  // the required occupied spost must be occupied by a different colour
  for (auto &c : p.requiredOccupied(dest)) {
    if (!pieceAt(c)) return false;
    if (listPieces[index(c)]->getColour() == p.getColour()) return false;
  }
  // the destination spot must not be occupied by the same colour
  if (pieceAt(dest, p.getColour())) return false;
  // If everything holds, then move can happen
  return true;
}

// Moves piece at source of specified colour to dest (throws exception if 
// piece does not exist there, piece is invalid or move is invalid)
// Used by public move(...), allMoves(...)
// Changes whose turn it is
void Board::move(Coord source, Coord dest, Type promo, Colour colour) {
  if (!pieceAt(source)) throw 1;  //incorrect piece
  Piece &p = *listPieces[index(source)];
  if (p.getColour() != colour) throw 2;  //incorrect piece
  if (!canMove(p, dest)) throw 3;  //incorrect move
  
  // Determine if the move is a special move
  bool left_enpassant=false, right_enpassant=false,
    left_castle=false, right_castle=false;
  // enpassant
  if (p.getType() == Type::Pawn
    && source.row != dest.row && source.col != dest.col) {
    // left_enpassant
    if (pieceAt(source.row, source.col-1)) {
      Piece &c = *listPieces[index(source.row, source.col-1)];
      if (c.getType() == Type::Pawn && c.getColour() != p.getColour()
        && stackMove.back().dest == c.getPos()
        && ( stackMove.back().source.row == c.getPos().row-2
        || stackMove.back().source.row == c.getPos().row+2 ) ) {
        left_enpassant=true;
      }
    }
    // right_enpassant
    if (pieceAt(source.row, source.col+1)) {
      Piece &c = *listPieces[index(source.row, source.col+1)];
      if (c.getType() == Type::Pawn && c.getColour() != p.getColour()
        && stackMove.back().dest == c.getPos()
        && ( stackMove.back().source.row == c.getPos().row-2
        || stackMove.back().source.row == c.getPos().row+2 ) ) {
        right_enpassant=true;
      }
    }
  }
  // castle
  if (p.getType() == Type::King) {
    // left_castle
    if (p.getPos().col-2 == dest.col) {
      left_castle = true;
    }
    // right_castle
    if (p.getPos().col+2 == dest.col) {
      right_castle = true;
    }
  }
  
  // Perform move and undo if king is left in check
  if (left_enpassant) {
    PastMove m{source, dest, p.getType()};
    p.setPos(dest);
    int i = index(source.row, source.col-1);
    m.capture = std::move(listPieces[i]);
    listPieces.erase(listPieces.begin()+i);
    Colour otherColour
      = (p.getColour()==Colour::White) ? Colour::Black : Colour::White;
    if (check(otherColour)) m.check=true;
    stackMove.emplace_back(std::move(m));
    if (check(p.getColour())) {
      undo();
      throw 4;  //incorrect move
    }
  } else if (right_enpassant) {
    PastMove m{source, dest, p.getType()};
    p.setPos(dest);
    int i = index(source.row, source.col+1);
    m.capture = std::move(listPieces[i]);
    listPieces.erase(listPieces.begin()+i);
    Colour otherColour
      = (p.getColour()==Colour::White) ? Colour::Black : Colour::White;
    if (check(otherColour)) m.check=true;
    stackMove.emplace_back(std::move(m));
    if (check(p.getColour())) {
      undo();
      throw 4;  //incorrect move
    }
  } else if (left_castle) {
    PastMove m{source, dest, p.getType()};
    p.setPos(dest);
    Coord rookSource{.row=source.row, .col=source.col-4};
    Coord rookDest{.row=source.row, .col=source.col-1};
    int i = index(rookSource);
    listPieces[i]->setPos(rookDest);
    unique_ptr<PastMove> t{new PastMove{rookSource, rookDest, Type::Rook}};
    m.additional = std::move(t);   // For some reason, make_unique isn't working
    Colour otherColour
      = (p.getColour()==Colour::White) ? Colour::Black : Colour::White;
    if (check(otherColour)) m.check=true;
    stackMove.emplace_back(std::move(m));
    if (check(p.getColour())) {
      undo();
      throw 4;  //incorrect move
    }
  } else if (right_castle) {
    PastMove m{source, dest, p.getType()};
    p.setPos(dest);
    Coord rookSource{.row=source.row, .col=source.col-4};
    Coord rookDest{.row=source.row, .col=source.col-1};
    int i = index(rookSource);
    listPieces[i]->setPos(rookDest);
    unique_ptr<PastMove> t{new PastMove{rookSource, rookDest, Type::Rook}};
    m.additional = std::move(t);   // For some reason, make_unique isn't working
    Colour otherColour
      = (p.getColour()==Colour::White) ? Colour::Black : Colour::White;
    if (check(otherColour)) m.check=true;
    stackMove.emplace_back(std::move(m));
    if (check(p.getColour())) {
      undo();
      throw 4;  //incorrect move
    }
  } else {  //general move
    PastMove m{source, dest, p.getType()};
    bool isapromo = isPromo(source, dest);
    if (isapromo && (promo == Type::King || promo == Type::Pawn)) {
      throw 5;  //incorrect move (promo type is wrong)
    }
    // capture
    if (pieceAt(dest)) {
      int i = index(dest);
      m.capture = std::move(listPieces[i]);
      listPieces.erase(listPieces.begin()+i);
    }
    // move
    p.setPos(dest);
    // promotion
    if (isapromo) {
      Colour pColour = p.getColour();
      int i = index(dest);
      m.oldPromo = std::move(listPieces[i]);
      listPieces.erase(listPieces.begin()+i);
      if (promo == Type::Queen) {
        unique_ptr<Queen> t{new Queen{dest, pColour, false}};
        listPieces.emplace_back(std::move(t));
      } else if (promo == Type::Rook) {
        unique_ptr<Rook> u{new Rook{dest, pColour, false}};
        listPieces.emplace_back(std::move(u));
      } else if (promo == Type::Bishop) {
        unique_ptr<Bishop> v{new Bishop{dest, pColour, false}};
        listPieces.emplace_back(std::move(v));
      } else if (promo == Type::Knight) {
        unique_ptr<Knight> w{new Knight{dest, pColour, false}};
        listPieces.emplace_back(std::move(w));
      } else {
        // This should never execute
        throw 5;  //unexpected exception
      }
    }
    Colour otherColour
      = (p.getColour()==Colour::White) ? Colour::Black : Colour::White;
    if (check(otherColour)) m.check=true;
    // Put completed move on the stack and undo if king is in check
    stackMove.emplace_back(std::move(m));
    if (check(p.getColour())) {
      undo();
      throw 4;  //incorrect move
    }
  }
  nextColour();
}

Board::Board(vector<unique_ptr<Piece>> &&pieces, Colour c, int size)
  : listPieces{pieces}, kingWhite{nullptr}, kingBlack{nullptr},
    turn{c}, size{size} {
  // checking for kings
  for (auto &p : listPieces) {
    if (p->getType() == Type::King) {
      if (p->getColour() == Colour::White) {
        if (kingWhite != nullptr) throw 1;
        kingWhite = p.get();
      } else if (p->getColour() == Colour::Black) {
        if (kingBlack != nullptr) throw 1;
        kingBlack = p.get();
      }
    }
  }
  if (kingBlack == nullptr || kingWhite == nullptr) throw 1;

  // check for pieces out of bounds
  for (auto &p : listPieces) {
    int r=p->getPos().row, c=p->getPos().col;
    if (r<0 || size<=r || c<0 || size<=c) throw 2;
    if ((r==0 || r==size-1) && p->getType()==Type::Pawn) throw 2;
  }

  // check for kings already in check
  if (check(Colour::White) || check(Colour::Black)) throw 3;
}
Board::Board(const Board &b)
  : kingWhite{nullptr}, kingBlack{nullptr},
    turn{b.getTurn()}, size{b.getSize()} {
  for (int i=0; i<b.numPieces(); ++i) {
    listPieces.emplace_back(make_unique<Piece>(&b.getPiece(i)));
  }
  // Other checks (like in the regular constructor) shouldn't
  // be necessary because the passed board should already be valid
}
Board::~Board() {
  // deallocation dealt with by unique_ptr
}

// Undoes a move (throws exception if stackMove is empty)
// Changes whose turn it is
void Board::undo() {
  // Check if stack is empty first
  if (stackMove.empty()) throw 1;
  undo(stackMove.back());
  stackMove.pop_back();
  prevColour();
}

// Moves piece at source with the colour of whoever's turn it is to dest
// (throws exception if piece does not exists there, piece is invalid or
// move is invalid)
// Changes whose turn it is (through call to private move(...) )
void Board::move(FutureMove f) {
  if (f.isPromo) move(f.source, f.dest, f.promoType);
  else move(f.source, f.dest);
}
void Board::move(Coord source, Coord dest, Type promo) {
  move(source, dest, promo, turn);
}
void Board::move(int sr, int sc, int dr, int dc, Type promo) {
  move(Coord{.row=sr, .col=sc}, Coord{.row=dr, .col=dc}, promo);
}

// Check if the king with colour c is in check
bool Board::check(Colour c) {
  Coord kingCoord;
  switch (c) {
  case Colour::White :
    kingCoord = kingWhite->getPos();
    break;
  case Colour::Black :
    kingCoord = kingBlack->getPos();
  }
  for (auto &p : listPieces) {
    if (p->getColour() == c) continue;
    if (canMove(*p, kingCoord)) return true;
  }
  // If none of the pieces with a different colour than c can
  // attack kingCoord, then the king is not in check
  return false;
}

// NOTE: CAN MAKE MORE EFFICIENT BY DERIVING FROM ALLMOVES,
//       BUT THIS IS USED FOR DEBUGGING PURPOSES///////////////////////////
bool Board::checkmate(Colour c) {
  return ( allMoves(c).size() == 0 );
}

bool Board::pieceAt(Coord c) {
  for (auto &p : listPieces) {
    if (p->getPos() == c) return true;
  }
  return false;
}
bool Board::pieceAt(int r, int c) {
  return pieceAt(Coord{.row=r, .col=c});
}
bool Board::pieceAt(Coord c, Colour colour) {
  for (auto &p : listPieces) {
    if (p->getColour() != colour) continue;
    if (p->getPos() == c) return true;
  }
  return false;
}
bool Board::pieceAt(int r, int c, Colour colour) {
  return pieceAt(Coord{.row=r, .col=c}, colour);
}

bool Board::outOfBounds(Coord c) {
  if (c.row<0 || size<=c.row || c.col<0 || size<=c.col) return true;
  return false;
}
bool Board::outOfBounds(int r, int c) {
  return outOfBounds(Coord{.row=r, .col=c});
}

// List all possible moves a certain colour can make
// (Note: pretty computationally expensive and unoptimized,
//        but solves lots of problems)
vector<FutureMove> Board::allMoves(Colour colour) {
  vector<FutureMove> f;
  for (auto &p : listPieces) {
    if (p->getColour() != colour) continue;
    Coord pCoord = p->getPos();
    for (int r=0; r<size; ++r) {
      for (int c=0; c<size; ++c) {
        Coord dest{.row=r, .col=c};
        try {
          move(pCoord, dest, Type::Queen, colour);
          undo();
          if (isPromo(pCoord, dest)) {
            f.emplace_back(FutureMove{pCoord, dest, true, Type::Queen});
            f.emplace_back(FutureMove{pCoord, dest, true, Type::Rook});
            f.emplace_back(FutureMove{pCoord, dest, true, Type::Bishop});
            f.emplace_back(FutureMove{pCoord, dest, true, Type::Knight});
          } else  {
            f.emplace_back(FutureMove{pCoord, dest, false, Type::Queen});
          }
        } catch (int e) {}
        //Catch the exceptions thrown by move; ignore them and continue
      }
    }
  }
  return f;
}

// NOTE: CAN MAKE MORE EFFICIENT BY DERIVING FROM ALLMOVES,
//       BUT THIS IS USED FOR DEBUGGING PURPOSES///////////////////////////
int Board::numAllMoves(Colour c) {
  return allMoves(c).size();
}

bool Board::isPromo(Coord source, Coord dest) {
  if (!pieceAt(source)) return false;
  Piece &p = *listPieces[index(source)];
  if (p.getType() != Type::Pawn) return false;
  switch (p.getColour()) {
  case Colour::White :
    if (dest.row == size-1) return true;
    break;
  case Colour::Black :
    if (dest.row == 0) return true;
  }
  return false;
}
bool Board::isPromo(int sr, int sc, int dr, int dc) {
  return isPromo(Coord{.row=sr, .col=sc}, Coord{.row=dr, .col=dc});
}

int Board::numPieces() const {
  return listPieces.size();
}
const Piece &Board::getPiece(int i) const {
  if (i<0 || listPieces.size()<=i) throw 1;
  return *listPieces[i].get();
}
int Board::numMoves() const {
  return stackMove.size();
}
const PastMove &Board::getMove(int i) const {
  if (i<0 || stackMove.size()<=i) throw 1;
  return stackMove[i];
}

Colour Board::getTurn() const {
  return turn;
}
int Board::getSize() const {
  return size;
}




/////////////////////////////////////////////////////////////
int main() {}