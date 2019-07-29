#include "piece.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "move.h"
#include "futuremove.h"
#include "colour.h"
#include "coord.h"
#include "type.h"
#include <vector>
#include <memory>
#include <utility>

using namespace std;

////////////////////////////////////////////////////////
// Replace throw with something sensible
////////////////////////////////////////////////////////

void Board::forceMove(Coord source, Coord dest) {
  // Check if piece exists at source before moving
  if (!pieceAt(source)) throw 1;
  stackMove.emplace_back(Move{source, dest});
  if (pieceAt(dest)) {
    int k = index(dest);
    stackMove.back().capture = move(listPieces[k]);
    listPieces.erase(listPieces.begin()+k);
  }
  listPieces[index(source)]->setPos(dest);
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
void Board::undo(Move &m) {
  // undo m.additional first
  if (m.additional.get() != nullptr) undo(*m.additional);
  int i = index(m.dest);
  // replace the promotion (if there is one)
  if (m.oldPromo.get() != nullptr) {
    listPieces.erase(listPieces.begin()+k);
    listPieces.emplace_back(move(m.oldPromo));
    i = listPieces.size() - 1;
  }
  // undo the move
  listPieces[i]->setPos(m.source);
  // replace the capture
  listPieces.emplace_back(move(m.capture));
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
}

void Board::move(Coord source, Coord dest, Type promo, Colour colour) {
  if (!pieceAt(source)) throw 1;  //incorrect piece
  Piece &p = *listPieces[index(source)];
  if (p.getColour() != colour) throw 2;  //incorrect piece
  if (!canMove()) throw 3;  //incorrect move
  
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
    m.capture = move(listPieces[i]);
    listPieces.erase(listPieces.begin()+i);
    stackMove.emplace_back(move(m));
    if (check(p.getColour())) {
      undo();
      throw 4;  //incorrect move
    }
  } else if (right_empassant) {
    PastMove m{source, dest, p.getType()};
    p.setPos(dest);
    int i = index(source.row, source.col+1);
    m.capture = move(listPieces[i]);
    listPieces.erase(listPieces.begin()+i);
    stackMove.emplace_back(move(m));
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
    m.additional = move(make_unique<PastMove>(
      new PastMove{rookSource, rookDest, Type::Rook}));
    stackMove.emplace_back(move(m));
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
    m.additional = move(make_unique<PastMove>(
      new PastMove{rookSource, rookDest, Type::Rook}));
    stackMove.emplace_back(move(m));
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
      m.capture = move(listPieces[i]);
      listPieces.erase(listPieces.begin()+i);
    }
    // move
    p.setPos(dest);
    // promotion
    if (isapromo) {
      int i = index(dest);
      m.oldPromo = move(listPieces[i]);
      listPieces.erase(listPieces.begin()+i);
    }
    // Put completed move on the stack and undo if king is in check
    stackMove.emplace_back(move(m));
    if (check(p.getColour())) {
      undo();
      throw 4;  //incorrect move
    }
  }
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
    if ((r==0 || r==size-1) && p->getType()==Pawn) throw 2;
  }

  // check for kings already in check
  if (check(Colour::White) || check(Colour::Black)) throw 3;
}
Board::Board(const Board &b)
  : kingWhite{nullptr}, kingBlack{nullptr},
    turn{b.getColour()}, size{b.getSize()} {
  for (const auto &p : b) {
    listPieces.emplace_back(make_unique<Piece>(p));
  }
  // Other checks (like in the regular constructor) shouldn't
  // be necessary because the passed board should already be valid
}
Board::~Board() {
  // deallocation dealt with by unique_ptr
}

void Board::undo() {
  // Check if stack is empty first
  if (stackMove.empty()) throw 1;
  undo(stackMove.back());
  stackMove.pop_back();
  prevColour();
}

void Board::move(FutureMove f) {
  if (f.isPromo) move(f.source, f.dest, f.type);
  else move(f.source, f.dest);
}
void Board::move(Coord source, Coord dest, Type promo) {
  move(source, dest, promo, turn);
}
void Board::move(int sr, int sc, int dr, int dc, Type promo) {
  move(Coord{.row=sr, .col=sc}, Coord{.row=dr, .row=dc}, promo);
}

// Check if the king with colour c is in check
bool check(Colour c) {
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
bool checkmate(Colour c) {
  return ( allMoves(c).size() == 0 );
}

bool pieceAt(Coord c) {
  for (auto &p : listPieces) {
    if (p->getPos() == c) return true;
  }
  return false;
}
bool pieceAt(int r, int c) {
  return pieceAt(Coord{.row=r, .col=c});
}
bool pieceAt(Coord c, Colour colour) {
  for (auto &p : listPieces) {
    if (p->getColour() != colour) continue;
    if (p->getPos() == c) return true;
  }
  return false;
}
bool pieceAt(int r, int c, Colour colour) {
  return pieceAt(Coord{.row=r, .col=c}, colour);
}

bool outOfBounds(Coord c) {
  if (c.row<0 || size<=c.row || c.col<0 || size<=c.col) return true;
  return false;
}
bool outOfBounds(int r, int c) {
  return outOfBounds(Coord{.row=r, .col=c});
}

// List all possible moves a certain colour can make
// (Note: pretty computationally expensive and unoptimized,
//        but solves lots of problems)
vector<FutureMove> allMoves(Colour c) {
  vector<FutureMove> f;
  for (auto &p : listPieces) {
    if (p->getColour() != c) continue;
    Coord pCoord = p->getPos();
    for (int r=0; r<size; ++r) {
      for (int c=0; c<size; ++c) {
        Coord dest{.row=r, .col=c};
        try {
          move(pCoord, dest, Type::Queen, c);
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
  return move(f);
}

// NOTE: CAN MAKE MORE EFFICIENT BY DERIVING FROM ALLMOVES,
//       BUT THIS IS USED FOR DEBUGGING PURPOSES///////////////////////////
int numAllMoves(Colour c) {
  return allMoves(c).size();
}

bool isPromo(Coord source, Coord dest) {
  if (!pieceAt(source)) return false;
  Piece &p = *listPieces[index(source)];
  if (p.type != Type::Pawn) return false;
  switch (p.colour) {
  case Colour::White :
    if (dest.row = size-1) return true;
    break;
  case Colour::Black :
    if (dest.row = 0) return true;
  }
  return false;
}
bool isPromo(int sr, int sc, int dr, int dc) {
  return isPromo(Coord{.row=sr, .col=sc}, Coord{.row=dr, .col=dc});
}

int numPieces() const {
  return listPieces.size();
}
const Piece &getPiece(int i) const {
  if (i<0 || listPieces.size()<=i) throw 1;
  return listPieces[i];
}
int numMoves() const {
  return stackMove.size();
}
const PastMove &getMove(int i) const {
  if (i<0 || stackMove.size()<=i) throw 1;
  return stackMove[i];
}

Colour getTurn() const {
  return turn;
}
int getSize() const {
  return size;
}

