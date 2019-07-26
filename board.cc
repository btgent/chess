#include "piece.h"
#include "move.h"          // Subject to change
#include "futuremove.h"    // Need to add
#include "colour.h"
#include "coord.h"
#include "type.h"
#include <vector>
#include <utility>

using namespace std;

// Replace throw with something sensible
Board::Board(vector<Piece*> pieces, int size)
  : kingWhite{nullptr}, kingBlack{nullptr}, size{size} {
  for (auto &p : pieces) {
    if (p->getType() == Type::King) {
      if (p->getColour() == Colour::White) {
        if (kingWhite != nullptr) throw 1;
        kingWhite = p;
      } else if (p->getColour() == Colour::Black) {
        if (kingBlack != nullptr) throw 1;
        kingBlack = p;
      }
    }
  }
  if (kingBlack == nullptr || kingWhite == nullptr) throw 1;

  for (auto &p : pieces) {
    int r=p->getCoord().row, c=p->getCoord().col;
    if (r<0 || size<=r || c<0 || size<=c) throw 2;
    if ((r==0 || r==size-1) && p->getType()==Pawn) throw 2;
  }

  if (check(Colour::White) || check(Colour::Black)) throw 3;

  listPieces = move(pieces);
}

Board::~Board() {
  for (auto &p : listPieces) {
    delete p;
  }
  // Destructor for Move must deallocate the pointers
}

void Board::forceMove(Coord source, Coord dest) {
  if (!pieceAt(source)) throw 1;
  stackMove.emplace_back(Move{source, dest});  //Don't know the format
  Move &m = stackMove.back();
  if (pieceAt(dest)) {
    int k = index(dest);
    m.capture = move(listPieces[k]);
    listPieces.erase(k);
  }
  int i = index(source);
  listPieces[i]->setCoord(dest);
}

int index(Coord c) {
  int vectorSize = listPieces.size();
  for (int i=0; i<vectorSize; ++i) {
    if (listPieces[i].getCoord() == c) return i;
  }
  throw 1;
}

void Board::undo() {
  //To do "additional", need undo(Move&)
  if (stackMove.empty()) throw 1;
  Move &m = stackMove.back();

  if (m.oldPromo != nullptr) {
    int i = index(m.dest);
    delete listPieces[i];
    listPieces[i] = m.oldPromo;
  }

  int i = index(m.dest);
  if (listPieces[i] == nullptr) throw 100;
  listPieces[i]->setCoord(m.source);

  if (m.capture != nullptr) {
    listPieces.emplace_back(m.capture);
  }

  stackMove.pop_back();
}

// No promotions for now (or anything fancy)
// There should be a method for canMove(Piece*, Coord dest)
// (Though not for move(...), for check(Colour)
void Board::move(Coord source, Coord dest, Colour c) {
  if (outOfBounds(dest)) throw 1;
  if (!pieceAt(source)) throw 2;
  int i = index(source);
  if (listPieces[i]->getColour() != c) throw 3;
  if (!listPieces[i]->possibleMove(dest)) throw 4;
  for (auto &c : listPieces[i]->requiredEmpty(dest)) {
    if (pieceAt(c)) throw 4;
  }
  // Should be a requiredFull method for Piece
  forceMove(source, dest);
  if (check(c)) {
    undo();
    throw 5;
  }
  undo();
  Move m{source, dest};
  if (pieceAt(dest)) {
    int k = index(dest);
    if (listPieces[k]->getColour() == c) throw 6;
    m.capture = move(listPieces[k]);
    listPieces.erase(k);
  }
  stackMove.emplace_back(move(m));  //Don't know the format
}

// Todo
bool check(Colour c) {
  return false;
}

// Todo
bool checkmate(Colour c) {
  return false;
}

bool pieceAt(Coord c) {
  for (auto &p : listPieces) {
    if (p->getCoord().equal(c)) return true;
  }
  return false;
}

bool outOfBounds(Coord c) {
  if (c.row<0 || size<=c.row || c.col<0 || size<=c.col) return true;
  return false;
}
