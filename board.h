#ifndef BOARD_H
#define BOARD_H

#include "pastmove.h"
#include "type.h"
#include <vector>
#include <memory>

class Piece;
class King;
class FutureMove;
class Colour;
class Coord;

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
  const int size;

  void forceMove(Coord, Coord);
  void forceMove(int, int, int, int);
  int index(Coord);
  int index(int, int);
  void nextColour();
  void prevColour();
  void undo(Move &);
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
  Colour getTurn() const;
  int getSize() const;
};

#endif
