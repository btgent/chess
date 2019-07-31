#include "board.h"
#include "coord.h"
#include "colour.h"
#include "type.h"
#include "piece.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "pastmove.h"
#include "futuremove.h"
#include "setupexception.h"
#include "pieceexception.h"
#include "moveexception.h"
#include "unexpectedexception.h"
#include <vector>
#include <memory>
#include <utility>
#include <sstream>

using namespace std;

// Forces piece at source to move to dest, without checking conditions
// Changes whose turn it is (because every forced move gets undone anyways,
// and undo() calls prevColour() )
// Any method that calls this must call undo() afterwards
void Board::forceMove(Coord source, Coord dest) {
  // Check if piece exists at source before moving
  if (!pieceAt(source)) {
    ostringstream oss;
    oss << "PieceException: Piece does not exist at (" << source.row << ", "
      << source.col << ")";
    throw PieceException{oss.str()};
  }
  Piece &p = *listPieces[index(source)];
  bool fm = p.isFirstMove();
  stackMove.emplace_back(PastMove{source, dest, Type::Queen, false, fm});
  if (pieceAt(dest)) {
    int k = index(dest);
    stackMove.back().capture = std::move(listPieces[k]);
    listPieces.erase(listPieces.begin()+k);
  }
  p.setPos(dest);
  nextColour();
}
void Board::forceMove(int sr, int sc, int dr, int dc) {
  forceMove(Coord{.row=sr, .col=sc}, Coord{.row=dr, .col=dc});
}

// Find index in listPieces where there is a piece with
// the passed coordinates
int Board::index(Coord loc) const {
  int i=0;
  for (auto &p : listPieces) {
    if (p->getPos() == loc) return i;
    ++i;
  }
  ostringstream oss;
  oss << "PieceException: Piece does not exist at (" << loc.row << ", "
    << loc.col << ")";
  throw PieceException{oss.str()};
  return 0;
}
int Board::index(int r, int c) const {
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
  listPieces[i]->setFirstMove(m.firstMove);
  // replace the capture (if there is one)
  if (m.capture.get() != nullptr) {
    listPieces.emplace_back(std::move(m.capture));
  }
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
        if (c.getType() == Type::Pawn && !stackMove.empty() 
          && stackMove.back().dest == c.getPos()
          && stackMove.back().source.row == c.getPos().row+2)
          return true;
      }
      // Check for right_enpassant
      if (pieceAt(right_enpassant)
        && !pieceAt(right_enpassant, p.getColour())) {
        Piece &c = *listPieces[index(right_enpassant)];
        if (c.getType() == Type::Pawn && !stackMove.empty()
          && stackMove.back().dest == c.getPos()
          && stackMove.back().source.row == c.getPos().row+2)
          return true;
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
        if (c.getType() == Type::Pawn && !stackMove.empty()
          && stackMove.back().dest == c.getPos()
          && stackMove.back().source.row == c.getPos().row-2)
          return true;
      }
      // Check for right_empassant
      if (pieceAt(right_enpassant)
        && !pieceAt(right_enpassant, p.getColour())) {
        Piece &c = *listPieces[index(right_enpassant)];
        if (c.getType() == Type::Pawn && !stackMove.empty()
          && stackMove.back().dest == c.getPos()
          && stackMove.back().source.row == c.getPos().row-2)
          return true;
      }
    }
  }
  // (castle)
  if (p.getType() == Type::King && p.isFirstMove()) {
    // Check left castle
    if (dest.row == pCoord.row && dest.col == pCoord.col-2
      && pieceAt(pCoord.row, pCoord.col-4, p.getColour())) {
      Piece &r = *listPieces[index(pCoord.row, pCoord.col-4)];
      if (r.getType() == Type::Rook && r.isFirstMove()
        && !pieceAt(pCoord.row, pCoord.col-1)
        && !pieceAt(pCoord.row, pCoord.col-2)
        && !pieceAt(pCoord.row, pCoord.col-3)
        && !check(p.getColour())) {
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
        && !pieceAt(pCoord.row, pCoord.col+2)
        && !check(p.getColour())) {
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
// Any method that calls this without going through public move(...)
// must call undo() afterwards
void Board::move(Coord source, Coord dest, Type promo, Colour colour) {
  if (setupMode) {
    throw SetupException{"SetupException: Can't use "
      "move(Coord, Coord, Type, Colour) while in setup mode"};
  }
  if (!pieceAt(source)) {
    ostringstream oss;
    oss << "PieceException: Piece does not exist at (" << source.row
      << ", " << source.col << ")";
    throw PieceException{oss.str()};
  }
  Piece &p = *listPieces[index(source)];
  if (p.getColour() != colour) {
    ostringstream oss;
    oss << "PieceException: Piece is the wrong colour at (" << source.row
      << ", " << source.col << ")";
    throw PieceException{oss.str()};
  }
  if (!canMove(p, dest)) {
    ostringstream oss;
    oss << "MoveException: piece cannot move from (" << source.row
      << ", " << source.col << ") to (" << dest.row << ", " << dest.col << ")";
    throw MoveException{oss.str()};
  }
  
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
        && !stackMove.empty() && stackMove.back().dest == c.getPos()
        && ( stackMove.back().source.row == c.getPos().row-2
        || stackMove.back().source.row == c.getPos().row+2 ) ) {
        left_enpassant=true;
      }
    }
    // right_enpassant
    if (pieceAt(source.row, source.col+1)) {
      Piece &c = *listPieces[index(source.row, source.col+1)];
      if (c.getType() == Type::Pawn && c.getColour() != p.getColour()
        && !stackMove.empty() && stackMove.back().dest == c.getPos()
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
    PastMove m{source, dest, p.getType(), false, p.isFirstMove()};
    p.setPos(dest);
    int i = index(source.row, source.col-1);
    m.capture = std::move(listPieces[i]);
    listPieces.erase(listPieces.begin()+i);
    Colour otherColour
      = (p.getColour()==Colour::White) ? Colour::Black : Colour::White;
    if (check(otherColour)) m.check=true;
    stackMove.emplace_back(std::move(m));
    if (check(p.getColour())) {
      nextColour();
      undo();
      throw MoveException{"MoveException: move puts king in check"};
    }
  } else if (right_enpassant) {
    PastMove m{source, dest, p.getType(), false, p.isFirstMove()};
    p.setPos(dest);
    int i = index(source.row, source.col+1);
    m.capture = std::move(listPieces[i]);
    listPieces.erase(listPieces.begin()+i);
    Colour otherColour
      = (p.getColour()==Colour::White) ? Colour::Black : Colour::White;
    if (check(otherColour)) m.check=true;
    stackMove.emplace_back(std::move(m));
    if (check(p.getColour())) {
      nextColour();
      undo();
      throw MoveException{"MoveException: move puts king in check"};
    }
  } else if (left_castle) {
    PastMove m{source, dest, p.getType(), false, p.isFirstMove()};
    p.setPos(dest);
    Coord rookSource{.row=source.row, .col=source.col-4};
    Coord rookDest{.row=source.row, .col=source.col-1};
    int i = index(rookSource);
    m.additional = make_unique<PastMove>(rookSource, rookDest, Type::Rook,
      false, listPieces[i]->isFirstMove());
    listPieces[i]->setPos(rookDest);
    Colour otherColour
      = (p.getColour()==Colour::White) ? Colour::Black : Colour::White;
    if (check(otherColour)) m.check=true;
    stackMove.emplace_back(std::move(m));
    if (check(p.getColour())) {
      nextColour();
      undo();
      throw MoveException{"MoveException: move puts king in check"};
    }
  } else if (right_castle) {
    PastMove m{source, dest, p.getType()};
    p.setPos(dest);
    Coord rookSource{.row=source.row, .col=source.col+3};
    Coord rookDest{.row=source.row, .col=source.col+1};
    int i = index(rookSource);
    m.additional = make_unique<PastMove>(rookSource, rookDest, Type::Rook,
      false, listPieces[i]->isFirstMove());
    listPieces[i]->setPos(rookDest);
    Colour otherColour
      = (p.getColour()==Colour::White) ? Colour::Black : Colour::White;
    if (check(otherColour)) m.check=true;
    stackMove.emplace_back(std::move(m));
    if (check(p.getColour())) {
      nextColour();
      undo();
      throw MoveException{"MoveException: move puts king in check"};
    }
  } else {  //general move
    PastMove m{source, dest, p.getType(), false, p.isFirstMove()};
    bool isapromo = isPromo(source, dest);
    // Change this and the switch statement below if you want a type to be
    // available for promotion (from pawn)
    if (isapromo && !(promo == Type::Queen || promo == Type::Rook
      || promo == Type::Bishop || promo == Type::Knight)) {
      throw MoveException{"MoveException: cannot promote to given type"};
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
      switch (promo) {
      case Type::Queen :
        listPieces.emplace_back(make_unique<Queen>(dest, pColour, false));
        break;
      case Type::Rook :
        listPieces.emplace_back(make_unique<Rook>(dest, pColour, false));
        break;
      case Type::Bishop :
        listPieces.emplace_back(make_unique<Bishop>(dest, pColour, false));
        break;
      case Type::Knight :
        listPieces.emplace_back(make_unique<Knight>(dest, pColour, false));
        break;
      default :
        listPieces.emplace_back(make_unique<Queen>(dest, pColour, false));
        stackMove.emplace_back(std::move(m));
        nextColour();
        undo();
        throw UnexpectedException{"UnexpectedException: code not given for "
        "requested promotion"};
      }
    }
    // Note: this changes when you add more colours to enum
    Colour otherColour
      = (p.getColour()==Colour::White) ? Colour::Black : Colour::White;
    if (check(otherColour)) m.check=true;
    // Put completed move on the stack and undo if king is in check
    stackMove.emplace_back(std::move(m));
    if (check(p.getColour())) {
      nextColour();
      undo();
      throw MoveException{"MoveException: move puts king in check"};
    }
  }
  nextColour();
}

Board::Board(bool setupMode, int size)
  : kingWhite{nullptr}, kingBlack{nullptr}, turn{Colour::White},
  setupMode{setupMode}, size{size} {
  // if setupMode is on, no pieces are placed by default
  if (setupMode) return;
  // if setupMode is off, then size must be 8 for default pieces to make sense
  if (size != 8) {
    throw SetupException{"SetupException: setupMode is false in "
      "Board constructor while size is not 8"};
  }
  for (int i=0; i<8; ++i) {
    // place white pawns
    listPieces.emplace_back(make_unique<Pawn>(Coord{.row=1, .col=i}, Colour::White));
    // place black pawns
    listPieces.emplace_back(make_unique<Pawn>(Coord{.row=6, .col=i}, Colour::Black));
  }
  // place other white pieces
  listPieces.emplace_back(make_unique<Rook>(Coord{.row=0, .col=0}, Colour::White));
  listPieces.emplace_back(make_unique<Knight>(Coord{.row=0, .col=1}, Colour::White));
  listPieces.emplace_back(make_unique<Bishop>(Coord{.row=0, .col=2}, Colour::White));
  listPieces.emplace_back(make_unique<Queen>(Coord{.row=0, .col=3}, Colour::White));
  listPieces.emplace_back(make_unique<King>(Coord{.row=0, .col=4}, Colour::White));
  listPieces.emplace_back(make_unique<Bishop>(Coord{.row=0, .col=5}, Colour::White));
  listPieces.emplace_back(make_unique<Knight>(Coord{.row=0, .col=6}, Colour::White));
  listPieces.emplace_back(make_unique<Rook>(Coord{.row=0, .col=7}, Colour::White));
  // place other black pieces
  listPieces.emplace_back(make_unique<Rook>(Coord{.row=7, .col=0}, Colour::Black));
  listPieces.emplace_back(make_unique<Knight>(Coord{.row=7, .col=1}, Colour::Black));
  listPieces.emplace_back(make_unique<Bishop>(Coord{.row=7, .col=2}, Colour::Black));
  listPieces.emplace_back(make_unique<Queen>(Coord{.row=7, .col=3}, Colour::Black));
  listPieces.emplace_back(make_unique<King>(Coord{.row=7, .col=4}, Colour::Black));
  listPieces.emplace_back(make_unique<Bishop>(Coord{.row=7, .col=5}, Colour::Black));
  listPieces.emplace_back(make_unique<Knight>(Coord{.row=7, .col=6}, Colour::Black));
  listPieces.emplace_back(make_unique<Rook>(Coord{.row=7, .col=7}, Colour::Black));
  
  kingWhite = listPieces[20].get();
  kingBlack = listPieces[28].get();
  moveFirst = turn = Colour::White;
}
Board::Board(const Board &b)
  : kingWhite{nullptr}, kingBlack{nullptr},
    turn{b.getTurn()}, size{b.getSize()} {
  for (int i=0; i<b.numPieces(); ++i) {
    listPieces.emplace_back(unique_ptr<Piece>(b.getPiece(i).clone()));
  }
  // find king pieces
  for (auto &p : listPieces) {
    if (p->getType() == Type::King) {
      if (p->getColour() == Colour::White) {
        if (kingWhite != nullptr) {
          throw UnexpectedException{"UnexpectedException: Board that is "
            "being copied has multiple kings of same colour"};
        }
        kingWhite = p.get();
      } else if (p->getColour() == Colour::Black) {
        if (kingBlack != nullptr) {
          throw UnexpectedException{"UnexpectedException: Board that is "
            "being copied has multiple kings of same colour"};
        }
        kingBlack = p.get();
      }
    }
  }
  if (kingBlack == nullptr || kingWhite == nullptr) {
    throw UnexpectedException{"UnexpectedException: Board that is "
    "being copied is missing kings"};
  }
  // Other checks (like in the regular constructor) shouldn't
  // be necessary because the passed board should already be valid
}
Board::~Board() {
  // deallocation dealt with by unique_ptr
}

void Board::place(Coord pCoord, Colour pColour, Type pType, bool firstMove) {
  if (!setupMode) {
    throw SetupException{"SetupException: Can't use "
      "place(Coord, Colour, Type, bool firstMove=true) while in non-setup mode"};
  }
  if (outOfBounds(pCoord)) {
    ostringstream oss;
    oss << "PieceException: Piece cannot be placed out of bounds: ("
      << pCoord.row << ", " << pCoord.col << ")";
    throw PieceException{oss.str()};
  }
  if (pieceAt(pCoord)) {
    listPieces.erase(listPieces.begin()+index(pCoord));
  }
  switch (pType) {
  case Type::King :
    listPieces.emplace_back(make_unique<King>(pCoord, pColour, firstMove));
    break;
  case Type::Queen :
    listPieces.emplace_back(make_unique<Queen>(pCoord, pColour, firstMove));
    break;
  case Type::Rook :
    listPieces.emplace_back(make_unique<Rook>(pCoord, pColour, firstMove));
    break;
  case Type::Bishop :
    listPieces.emplace_back(make_unique<Bishop>(pCoord, pColour, firstMove));
    break;
  case Type::Knight :
    listPieces.emplace_back(make_unique<Knight>(pCoord, pColour, firstMove));
    break;
  case Type::Pawn :
    listPieces.emplace_back(make_unique<Pawn>(pCoord, pColour, firstMove));
  }
}

void Board::remove(Coord coord) {
  if (!setupMode) {
    throw SetupException{"SetupException: Can't use "
      "remove(Coord) while in non-setup mode"};
  }
  if (!pieceAt(coord)) {
    ostringstream oss;
    oss << "PieceException: Piece does not exist at (" << coord.row
      << ", " << coord.col << ")";
    throw PieceException{oss.str()};
  }
  listPieces.erase(listPieces.begin()+index(coord));
}

void Board::changeStartTurn(Colour colour) {
  if (!setupMode) {
    throw SetupException{"SetupException: Can't use "
      "changeStartTurn(Colour) while in non-setup mode"};
  }
  turn = colour;
}

void Board::exitSetup() {
  if (!setupMode) {
    throw SetupException{"SetupException: Can't use "
      "exitSetup() while in non-setup mode"};
  }
  // checking for kings
  for (auto &p : listPieces) {
    if (p->getType() == Type::King) {
      if (p->getColour() == Colour::White) {
        if (kingWhite != nullptr) {
          kingWhite = kingBlack = nullptr;
          throw SetupException{"SetupException: Cannot exit setup mode: "
          "found multiple kings with same colour"};
        }
        kingWhite = p.get();
      } else if (p->getColour() == Colour::Black) {
        if (kingBlack != nullptr) {
          kingWhite = kingBlack = nullptr;
          throw SetupException{"SetupException: Cannot exit setup mode: "
          "found multiple kings with same colour"};
        }
        kingBlack = p.get();
      }
    }
  }
  if (kingBlack == nullptr || kingWhite == nullptr) {
    kingWhite = kingBlack = nullptr;
    throw SetupException{"SetupException: Cannot exit setup mode: "
    "not enough kings found"};
  }

  // check for pieces out of bounds
  for (auto &p : listPieces) {
    int r=p->getPos().row, c=p->getPos().col;
    if (r<0 || size<=r || c<0 || size<=c) {
      kingWhite = kingBlack = nullptr;
      throw SetupException{"SetupException: Cannot exit setup mode: "
      "found pieces that are out of bounds"};
    }
    if ((r==0 || r==size-1) && p->getType()==Type::Pawn) {
      kingWhite = kingBlack = nullptr;
      throw SetupException{"SetupException: Cannot exit setup mode: "
      "found pawns that are on the first/last row"};
    }
  }

  // Need to set setupMode to false to use check(...)
  setupMode = false;

  // check for kings already in check
  if (check(Colour::White) || check(Colour::Black)) {
    kingWhite = kingBlack = nullptr;
    setupMode = true;
    throw SetupException{"SetupException: Cannot exit setup mode: "
    "found kings in check"};
  }
  
  // if everything works, exit setup mode
  moveFirst = turn;
  setupMode = false;
}



// Undoes a move (throws exception if stackMove is empty)
// Changes whose turn it is
void Board::undo() {
  if (setupMode) {
    throw SetupException{"SetupException: Can't use "
      "undo() while in setup mode"};
  }
  // Check if stack is empty first
  if (stackMove.empty()) {
    throw MoveException{"MoveException: No moves in stack"};
  }
  undo(stackMove.back());
  stackMove.pop_back();
  prevColour();
}

// Moves piece at source with the colour of whoever's turn it is to dest
// (throws exception if piece does not exists there, piece is invalid or
// move is invalid)
// Changes whose turn it is (through call to private move(...) )
void Board::move(FutureMove f) {
  // checks that board is in setup mode when it ends up calling private move(...)
  if (f.isPromo) move(f.source, f.dest, f.promoType);
  else move(f.source, f.dest);
}
void Board::move(Coord source, Coord dest, Type promo) {
  // checks that board is in setup mode when it ends up calling private move(...)
  move(source, dest, promo, turn);
}
void Board::move(int sr, int sc, int dr, int dc, Type promo) {
  // checks that board is in setup mode when it ends up calling private move(...)
  move(Coord{.row=sr, .col=sc}, Coord{.row=dr, .col=dc}, promo);
}

// Check if the king with colour c is in check
bool Board::check(Colour c) {
  if (setupMode) {
    throw SetupException{"SetupException: Can't use "
      "check() while in setup mode"};
  }
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

bool Board::checkmate(Colour c) {
  if (setupMode) {
    throw SetupException{"SetupException: Can't use "
      "checkmate(Colour) while in setup mode"};
  }
  return check(c) && noMovesLeft(c);
}

bool Board::stalemate(Colour c) {
  if (setupMode) {
    throw SetupException{"SetupException: Can't use "
      "checkmate(Colour) while in setup mode"};
  }
  return !check(c) && noMovesLeft(c);
}

bool Board::noMovesLeft(Colour colour) {
  if (setupMode) {
    throw SetupException{"SetupException: Can't use "
      "allMoves(Colour) while in setup mode"};
  }
  for (auto &p : listPieces) {
    if (p->getColour() != colour) continue;
    Coord pCoord = p->getPos();
    for (int r=0; r<size; ++r) {
      for (int c=0; c<size; ++c) {
        Coord dest{.row=r, .col=c};
        try {
          move(pCoord, dest, Type::Queen, colour);
          undo();
          return false;
        } catch (runtime_error) {}
        //Catch the exceptions thrown by move(...); ignore them and continue
      }
    }
  }
  return true;
}

// List all possible moves a certain colour can make
// (Note: pretty computationally expensive and unoptimized,
//        but solves lots of problems)
vector<FutureMove> Board::allMoves(Colour colour) {
  if (setupMode) {
    throw SetupException{"SetupException: Can't use "
      "allMoves(Colour) while in setup mode"};
  }
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
        } catch (runtime_error) {}
        //Catch the exceptions thrown by move(...); ignore them and continue
      }
    }
  }
  return f;
}

int Board::numAllMoves(Colour colour) {
  if (setupMode) {
    throw SetupException{"SetupException: Can't use "
      "numAllMoves(Colour) while in setup mode"};
  }
  int n = 0;
  for (auto &p : listPieces) {
    if (p->getColour() != colour) continue;
    Coord pCoord = p->getPos();
    for (int r=0; r<size; ++r) {
      for (int c=0; c<size; ++c) {
        Coord dest{.row=r, .col=c};
        try {
          move(pCoord, dest, Type::Queen, colour);
          undo();
          ++n;
        } catch (runtime_error) {}
        //Catch the exceptions thrown by move(...); ignore them and continue
      }
    }
  }
  return n;
}


bool Board::pieceAt(Coord c) const {
  for (auto &p : listPieces) {
    if (p->getPos() == c) return true;
  }
  return false;
}
bool Board::pieceAt(int r, int c) const {
  return pieceAt(Coord{.row=r, .col=c});
}
bool Board::pieceAt(Coord c, Colour colour) const {
  for (auto &p : listPieces) {
    if (p->getColour() != colour) continue;
    if (p->getPos() == c) return true;
  }
  return false;
}
bool Board::pieceAt(int r, int c, Colour colour) const {
  return pieceAt(Coord{.row=r, .col=c}, colour);
}

bool Board::outOfBounds(Coord c) const {
  if (c.row<0 || size<=c.row || c.col<0 || size<=c.col) return true;
  return false;
}
bool Board::outOfBounds(int r, int c) const {
  return outOfBounds(Coord{.row=r, .col=c});
}

bool Board::isPromo(Coord source, Coord dest) const {
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
bool Board::isPromo(int sr, int sc, int dr, int dc) const {
  return isPromo(Coord{.row=sr, .col=sc}, Coord{.row=dr, .col=dc});
}

int Board::numPieces() const {
  return listPieces.size();
}
const Piece &Board::getPiece(int i) const {
  if (i<0 || static_cast<int>(listPieces.size())<=i) {
    ostringstream oss;
    oss << "PieceException: piece doesn't exist at index " << i << "in listPieces";
    throw PieceException{oss.str()};
  }
  return *listPieces[i].get();
}
int Board::numMoves() const {
  return stackMove.size();
}
const PastMove &Board::getMove(int i) const {
  if (i<0 || static_cast<int>(stackMove.size())<=i) {
    ostringstream oss;
    oss << "MoveException: move doesn't exist at index " << i << "in stackMove";
    throw MoveException{oss.str()};
  }
  return stackMove[i];
}

Colour Board::getTurn() const {
  return turn;
}
int Board::getSize() const {
  return size;
}

