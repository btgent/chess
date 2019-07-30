#ifndef BOARD_H
#define BOARD_H

#include "colour.h"
#include "type.h"
#include "pastmove.h"
#include <vector>
#include <memory>

class Coord;
class FutureMove;
class Piece;
class King;

// Board methods can throw SetupException, PieceException, MoveException,
// or UnexpectedException (which are all std::runtime_error)

// In the future, Board would be an abstract class,
// this would be StdBoard class, and there would be
// ExtraBoard class with additional functionality
// like nogo spaces and support for multiple colours.
// There could also be a ExtremeBoard with extra
// functions like placing pieces during the game
// and being able to perform multiple moves in the
// same turn (but that would require some changes to
// the underlying classes)
class Board {
  std::vector<std::unique_ptr<Piece>> listPieces;
  std::vector<PastMove> stackMove;
  Piece *kingWhite;
  Piece *kingBlack;
  Colour turn;
  Colour moveFirst;
  bool setupMode;
  const int size;

  void forceMove(Coord, Coord);
  void forceMove(int, int, int, int);
  int index(Coord);
  int index(int, int);
  void nextColour();
  void prevColour();
  void undo(PastMove &);
  bool canMove(Piece &, Coord dest);
  void move(Coord, Coord, Type, Colour);  // non-setup mode only

 public:
  Board(bool setupMode=false, int size=8);
  Board(const Board &b);
  Board &operator=(const Board &b) = delete;
  ~Board();

  // setup mode only
  void place(Coord, Colour, Type, bool firstMove=true);
  void remove(Coord);
  void changeStartTurn(Colour);
  void exitSetup();

  // non-setup mode only
  void undo();
  void move(FutureMove);
  void move(Coord, Coord, Type=Type::Queen);
  void move(int, int, int, int, Type=Type::Queen);
  bool check(Colour);
  bool checkmate(Colour);
  vector<FutureMove> allMoves(Colour);
  int numAllMoves(Colour);
  
  // Can be used at any time
  bool pieceAt(Coord);
  bool pieceAt(int, int);
  bool pieceAt(Coord, Colour);
  bool pieceAt(int, int, Colour);
  bool outOfBounds(Coord);
  bool outOfBounds(int, int);
  bool isPromo(Coord, Coord);
  bool isPromo(int, int, int, int);
  int numPieces() const;
  const Piece &getPiece(int i) const;
  int numMoves() const;
  const PastMove &getMove(int i) const;
  Colour getTurn() const;
  int getSize() const;
};

#endif
